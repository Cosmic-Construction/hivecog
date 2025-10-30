"""
EconomicBackpropagation - Gradient-based value flow through the planetary transformer

Money flows backward through the network like gradients in neural network training,
reinforcing successful patterns and pruning unsuccessful ones.
"""

import numpy as np
from typing import Dict, List, Set
from dataclasses import dataclass
from datetime import datetime


@dataclass
class ContributionMetric:
    """Tracks a city's contribution to solving a problem"""
    city_id: str
    value_contributed: float
    knowledge_provided: np.ndarray
    timestamp: datetime
    problem_id: str


@dataclass
class EvolutionaryPressure:
    """Represents selection pressure on city strategies"""
    survival_threshold: float
    reproduction_rate: float
    mutation_rate: float


class EconomicBackpropagation:
    """
    Implements economic gradient flow through the planetary transformer.
    
    Features:
    - Value-based gradient calculation
    - Resource allocation based on contribution
    - Evolutionary pressure on city strategies
    - Natural selection at transformer level
    """
    
    def __init__(
        self,
        learning_rate: float = 0.01,
        reputation_rate: float = 0.05,
        decay_rate: float = 0.95,
        survival_threshold: float = 1000.0
    ):
        self.learning_rate = learning_rate
        self.reputation_rate = reputation_rate
        self.decay_rate = decay_rate
        self.survival_threshold = survival_threshold
        
        # Track contributions and outcomes
        self.contribution_history: List[ContributionMetric] = []
        self.value_created_history: Dict[str, List[float]] = {}
        
        # Track city lineages for evolution
        self.city_lineages: Dict[str, List[str]] = {}
        
    def backward_pass(
        self,
        value_created: float,
        contributing_cities: List,
        non_contributing: List,
        problem_solution: Dict
    ) -> Dict[str, float]:
        """
        Flow value backward through network like gradient descent.
        
        Args:
            value_created: Total value created by the solution
            contributing_cities: Cities that helped solve the problem
            non_contributing: Cities that existed but didn't contribute
            problem_solution: Details of the problem and solution
            
        Returns:
            Dictionary mapping city_id to gradient (budget change)
        """
        gradients = {}
        
        # Calculate contribution for each city
        for city in contributing_cities:
            gradient = self.calculate_contribution(city, value_created)
            
            # Increase budget (like updating weights with positive gradient)
            city.budget += gradient * self.learning_rate
            
            # Increase reputation
            city.reputation += gradient * self.reputation_rate
            
            # Track the gradient
            gradients[city.city] = gradient
            
            # Record contribution
            self.contribution_history.append(ContributionMetric(
                city_id=city.city,
                value_contributed=gradient,
                knowledge_provided=np.array([]),  # Simplified
                timestamp=datetime.now(),
                problem_id=problem_solution.get('id', 'unknown')
            ))
        
        # Apply decay to non-contributing cities
        for city in non_contributing:
            # Reduce budget (negative gradient)
            budget_reduction = city.budget * (1 - self.decay_rate)
            city.budget *= self.decay_rate
            
            # Reduce reputation more slowly
            city.reputation *= 0.98
            
            gradients[city.city] = -budget_reduction
        
        return gradients
    
    def calculate_contribution(self, city, value_created: float) -> float:
        """
        Calculate how much a city contributed to the overall value.
        
        Args:
            city: The CityAsAttentionHead instance
            value_created: Total value created
            
        Returns:
            Gradient value (contribution score)
        """
        # Base contribution from participation
        base_contribution = value_created * 0.1
        
        # Bonus for specialization match
        specialization_bonus = value_created * 0.2 * city.reputation
        
        # Bonus for queries served
        service_bonus = min(city.total_queries_served * 0.5, value_created * 0.3)
        
        # Total contribution
        contribution = base_contribution + specialization_bonus + service_bonus
        
        return contribution
    
    def evolutionary_pressure(
        self,
        all_cities: List,
        current_generation: int
    ) -> List:
        """
        Apply evolutionary pressure - cities that don't contribute die,
        successful cities spawn variants.
        
        Args:
            all_cities: List of all CityAsAttentionHead instances
            current_generation: Current generation number
            
        Returns:
            Updated list of cities (some removed, some added)
        """
        surviving_cities = []
        new_cities = []
        
        for city in all_cities:
            if city.budget >= self.survival_threshold:
                # City survives
                surviving_cities.append(city)
                
                # High-performing cities reproduce
                if city.budget > self.survival_threshold * 3:
                    # Spawn a variant with mutated strategy
                    variant = self.spawn_variant(city, current_generation)
                    new_cities.append(variant)
            else:
                # City dies - record its lineage
                if city.city not in self.city_lineages:
                    self.city_lineages[city.city] = []
                self.city_lineages[city.city].append(f"died_gen_{current_generation}")
        
        # Return combined population
        return surviving_cities + new_cities
    
    def spawn_variant(self, parent_city, generation: int):
        """
        Create a variant of a successful city with mutations.
        
        Args:
            parent_city: The successful parent city
            generation: Current generation number
            
        Returns:
            New CityAsAttentionHead instance with mutated parameters
        """
        from .city_attention_head import CityAsAttentionHead
        
        # Create variant name
        variant_name = f"{parent_city.city}_variant_gen{generation}"
        
        # Mutate specialization (slight variation)
        specializations = [
            "traffic_management",
            "energy_optimization",
            "waste_reduction",
            "public_safety",
            "economic_development",
            "environmental_sustainability"
        ]
        
        # 80% chance to keep parent specialization, 20% to mutate
        if np.random.random() < 0.8:
            new_spec = parent_city.specialization
        else:
            new_spec = np.random.choice(specializations)
        
        # Create variant with inherited budget
        variant = CityAsAttentionHead(
            city_name=variant_name,
            specialization=new_spec,
            hidden_dim=parent_city.hidden_dim,
            num_districts=parent_city.num_districts,
            initial_budget=parent_city.budget * 0.3,  # Child gets 30% of parent's budget
            base_knowledge_price=parent_city.base_knowledge_price * np.random.uniform(0.8, 1.2)
        )
        
        # Inherit some reputation
        variant.reputation = parent_city.reputation * 0.7
        
        # Record lineage
        if parent_city.city not in self.city_lineages:
            self.city_lineages[parent_city.city] = []
        self.city_lineages[parent_city.city].append(variant_name)
        
        return variant
    
    def calculate_fitness(self, city) -> float:
        """
        Calculate fitness score for evolutionary selection.
        
        Args:
            city: CityAsAttentionHead instance
            
        Returns:
            Fitness score
        """
        # Fitness based on:
        # 1. Budget (resources)
        # 2. Reputation (quality)
        # 3. Value created (productivity)
        # 4. Queries served (usefulness)
        
        budget_score = city.budget / 10000.0
        reputation_score = city.reputation
        value_score = city.total_value_created / 1000.0
        service_score = city.total_queries_served / 100.0
        
        fitness = (
            budget_score * 0.3 +
            reputation_score * 0.3 +
            value_score * 0.2 +
            service_score * 0.2
        )
        
        return fitness
    
    def get_top_performers(
        self,
        all_cities: List,
        top_k: int = 10
    ) -> List:
        """
        Get the top performing cities by fitness.
        
        Args:
            all_cities: List of all cities
            top_k: Number of top performers to return
            
        Returns:
            List of top performing cities
        """
        # Calculate fitness for each city
        city_fitness = [
            (city, self.calculate_fitness(city))
            for city in all_cities
        ]
        
        # Sort by fitness
        city_fitness.sort(key=lambda x: x[1], reverse=True)
        
        # Return top k
        return [city for city, _ in city_fitness[:top_k]]
    
    def analyze_contribution_patterns(self) -> Dict:
        """
        Analyze patterns in city contributions over time.
        
        Returns:
            Dictionary with analysis results
        """
        if not self.contribution_history:
            return {
                'total_contributions': 0,
                'avg_contribution': 0,
                'top_contributors': [],
                'contribution_trend': []
            }
        
        # Aggregate by city
        city_contributions = {}
        for contrib in self.contribution_history:
            if contrib.city_id not in city_contributions:
                city_contributions[contrib.city_id] = []
            city_contributions[contrib.city_id].append(contrib.value_contributed)
        
        # Calculate statistics
        top_contributors = sorted(
            [
                (city_id, sum(values))
                for city_id, values in city_contributions.items()
            ],
            key=lambda x: x[1],
            reverse=True
        )[:10]
        
        total_value = sum(c.value_contributed for c in self.contribution_history)
        avg_value = total_value / len(self.contribution_history)
        
        return {
            'total_contributions': len(self.contribution_history),
            'total_value_created': total_value,
            'avg_contribution': avg_value,
            'top_contributors': top_contributors,
            'unique_contributors': len(city_contributions)
        }
    
    def get_lineage_tree(self, city_id: str) -> List[str]:
        """
        Get the evolutionary lineage of a city.
        
        Args:
            city_id: ID of the city
            
        Returns:
            List of descendant city IDs
        """
        return self.city_lineages.get(city_id, [])
