"""
CityAsAttentionHead - Core transformer attention mechanism for planetary neural network

Each city operates as an attention head in the global transformer architecture,
implementing both self-attention (within districts) and cross-attention (between cities).
"""

import numpy as np
from typing import Dict, List, Optional, Tuple
from dataclasses import dataclass, field
from datetime import datetime
import math


@dataclass
class DistrictQuery:
    """Represents a query from a district within a city"""
    district_id: str
    query_vector: np.ndarray
    urgency: float
    timestamp: datetime


@dataclass
class KnowledgeResponse:
    """Response containing knowledge from another city"""
    source_city: str
    value_vector: np.ndarray
    cost: float
    quality: float
    relevance_score: float


@dataclass
class AttentionWeights:
    """Calculated attention weights for cross-city attention"""
    city_weights: Dict[str, float]
    total_cost: float
    expected_quality: float


class CityAsAttentionHead:
    """
    Implements a city as an attention head in the planetary transformer.
    
    Features:
    - Self-attention within city districts
    - Cross-attention to other cities
    - Economic pressure as attention weights
    - Knowledge sharing with cost/value optimization
    """
    
    def __init__(
        self,
        city_name: str,
        specialization: str,
        hidden_dim: int = 512,
        num_districts: int = 8,
        initial_budget: float = 10000.0,
        base_knowledge_price: float = 10.0
    ):
        self.city = city_name
        self.specialization = specialization
        self.hidden_dim = hidden_dim
        self.num_districts = num_districts
        self.budget = initial_budget
        self.base_knowledge_price = base_knowledge_price
        
        # District-level neurons
        self.local_neurons: List[str] = [
            f"{city_name}_district_{i}" for i in range(num_districts)
        ]
        
        # Historical patterns and knowledge
        self.memory_bank: Dict[str, np.ndarray] = {}
        
        # Reputation and success metrics
        self.reputation = 1.0
        self.success_rate = 0.5
        self.total_queries_served = 0
        self.total_value_created = 0.0
        
        # Initialize district embeddings
        self.district_embeddings = np.random.randn(num_districts, hidden_dim) * 0.1
        
        # Query, Key, Value projection matrices for self-attention
        self.W_q = np.random.randn(hidden_dim, hidden_dim) * 0.01
        self.W_k = np.random.randn(hidden_dim, hidden_dim) * 0.01
        self.W_v = np.random.randn(hidden_dim, hidden_dim) * 0.01
        
    def self_attention(self, urban_query: Dict) -> np.ndarray:
        """
        Districts attend to each other to solve local urban challenges.
        
        Args:
            urban_query: Dictionary containing the urban challenge parameters
            
        Returns:
            Local solution vector from district coordination
        """
        # Generate queries from districts
        Q = self.district_embeddings @ self.W_q
        
        # Generate keys from district knowledge
        K = self.district_embeddings @ self.W_k
        
        # Generate values from district capabilities
        V = self.district_embeddings @ self.W_v
        
        # Calculate attention scores with economic pressure
        # Budget constraint affects attention temperature
        temperature = math.sqrt(self.hidden_dim) * (self.budget / 10000.0)
        attention_scores = Q @ K.T / temperature
        
        # Apply softmax to get attention weights
        attention_weights = self._softmax(attention_scores)
        
        # Generate local solution
        local_output = attention_weights @ V
        
        # Aggregate across districts
        solution = np.mean(local_output, axis=0)
        
        return solution
    
    def cross_attention(
        self,
        my_query: np.ndarray,
        other_cities: List['CityAsAttentionHead']
    ) -> Tuple[np.ndarray, float]:
        """
        This city attends to other cities to gather external knowledge.
        
        Args:
            my_query: Query vector representing the city's need
            other_cities: List of other CityAsAttentionHead instances
            
        Returns:
            Tuple of (synthesized_solution, total_cost)
        """
        responses = []
        total_cost = 0.0
        
        for city in other_cities:
            # Calculate relevance score
            relevance = self._calculate_relevance(my_query, city)
            
            # Get access cost
            access_cost = city.get_access_cost(relevance)
            
            # Check if we can afford this city's knowledge
            if self.can_afford(access_cost):
                # Request knowledge
                response = city.provide_knowledge(my_query, relevance)
                
                # Pay for the knowledge
                self.pay(city, access_cost)
                total_cost += access_cost
                
                # Weight by quality and relevance
                weighted_response = response * city.reputation * relevance
                responses.append(weighted_response)
        
        if not responses:
            # No affordable knowledge available, use local only
            return self.self_attention({}), 0.0
        
        # Synthesize responses
        solution = np.mean(responses, axis=0)
        
        return solution, total_cost
    
    def generate_query(self, problem_description: Dict) -> np.ndarray:
        """
        Generate a query vector from an urban problem description.
        
        Args:
            problem_description: Dictionary describing the urban challenge
            
        Returns:
            Query vector in hidden dimension space
        """
        # Simple encoding: hash problem features into vector space
        query = np.zeros(self.hidden_dim)
        
        # Encode problem type
        if 'type' in problem_description:
            type_hash = hash(problem_description['type']) % self.hidden_dim
            query[type_hash] = 1.0
        
        # Encode urgency
        if 'urgency' in problem_description:
            query *= problem_description['urgency']
        
        # Add specialization bias
        spec_hash = hash(self.specialization) % self.hidden_dim
        query[spec_hash] += 0.5
        
        return query
    
    def provide_knowledge(
        self,
        query: np.ndarray,
        relevance: float
    ) -> np.ndarray:
        """
        Provide knowledge to another city in response to their query.
        
        Args:
            query: Query vector from requesting city
            relevance: Relevance score of this city's knowledge
            
        Returns:
            Knowledge vector (value)
        """
        # Generate value from query using specialization
        value = query @ self.W_v.T
        
        # Modulate by our expertise in the area
        value *= relevance
        
        # Add our specialized knowledge
        spec_vector = np.random.randn(self.hidden_dim) * 0.1
        spec_hash = hash(self.specialization) % self.hidden_dim
        spec_vector[spec_hash] += 1.0
        
        value += spec_vector * self.reputation
        
        # Track that we served a query
        self.total_queries_served += 1
        
        return value
    
    def get_access_cost(self, relevance: float) -> float:
        """
        Calculate cost to access this city's knowledge.
        
        Args:
            relevance: How relevant our knowledge is to the query
            
        Returns:
            Cost in currency units
        """
        # Base cost adjusted by relevance and reputation
        cost = self.base_knowledge_price * relevance * self.reputation
        
        # Premium for high-demand specializations
        premium_multiplier = 1.0 + (self.total_queries_served / 1000.0)
        
        return cost * premium_multiplier
    
    def can_afford(self, cost: float) -> bool:
        """Check if city can afford the specified cost"""
        return self.budget >= cost
    
    def pay(self, recipient: 'CityAsAttentionHead', amount: float):
        """
        Transfer funds to another city for knowledge.
        
        Args:
            recipient: The city receiving payment
            amount: Amount to transfer
        """
        if self.budget >= amount:
            self.budget -= amount
            recipient.receive_payment(amount)
    
    def receive_payment(self, amount: float):
        """
        Receive payment for providing knowledge.
        
        Args:
            amount: Amount received
        """
        self.budget += amount
        self.total_value_created += amount
    
    def _calculate_relevance(
        self,
        query: np.ndarray,
        other_city: 'CityAsAttentionHead'
    ) -> float:
        """
        Calculate how relevant another city's knowledge is to our query.
        
        Args:
            query: Our query vector
            other_city: The city to evaluate
            
        Returns:
            Relevance score between 0.0 and 1.0
        """
        # Use cosine similarity between query and other city's specialization
        other_spec_vector = np.zeros(self.hidden_dim)
        spec_hash = hash(other_city.specialization) % self.hidden_dim
        other_spec_vector[spec_hash] = 1.0
        
        # Normalize
        query_norm = np.linalg.norm(query)
        spec_norm = np.linalg.norm(other_spec_vector)
        
        if query_norm == 0 or spec_norm == 0:
            return 0.1
        
        similarity = np.dot(query, other_spec_vector) / (query_norm * spec_norm)
        
        # Map to [0, 1] range
        relevance = (similarity + 1.0) / 2.0
        
        # Boost by reputation
        relevance *= other_city.reputation
        
        return max(0.0, min(1.0, relevance))
    
    def _softmax(self, x: np.ndarray) -> np.ndarray:
        """Compute softmax values for array x"""
        exp_x = np.exp(x - np.max(x, axis=-1, keepdims=True))
        return exp_x / np.sum(exp_x, axis=-1, keepdims=True)
    
    def update_reputation(self, feedback_score: float):
        """
        Update reputation based on feedback.
        
        Args:
            feedback_score: Score between 0.0 and 1.0
        """
        # Exponential moving average
        alpha = 0.1
        self.reputation = (1 - alpha) * self.reputation + alpha * feedback_score
        self.reputation = max(0.1, min(2.0, self.reputation))
    
    def get_state(self) -> Dict:
        """Get current state of the city attention head"""
        return {
            'city': self.city,
            'specialization': self.specialization,
            'budget': self.budget,
            'reputation': self.reputation,
            'success_rate': self.success_rate,
            'total_queries_served': self.total_queries_served,
            'total_value_created': self.total_value_created,
            'num_districts': self.num_districts
        }
