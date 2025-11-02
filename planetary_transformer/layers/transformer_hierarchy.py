"""
PlanetaryTransformerLayers - Multi-layer attention hierarchy for global consciousness

Implements the four-layer transformer architecture:
- Layer 1: Neighborhood (local, minutes-hours)
- Layer 2: Metropolitan (regional, hours-days)  
- Layer 3: Continental (macro-regional, days-weeks)
- Layer 4: Planetary (global, weeks-months)
"""

import numpy as np
from typing import Dict, List, Optional, Tuple
from dataclasses import dataclass
from datetime import datetime, timedelta
from enum import Enum


class TimeScale(Enum):
    """Time scales for different transformer layers"""
    MINUTES = "minutes"
    HOURS = "hours"
    DAYS = "days"
    WEEKS = "weeks"
    MONTHS = "months"


@dataclass
class LayerOutput:
    """Output from a transformer layer"""
    layer_name: str
    output_vector: np.ndarray
    attention_weights: Dict[str, float]
    processing_time: timedelta
    emergence_score: float


class TransformerLayer:
    """Base class for transformer layers"""
    
    def __init__(
        self,
        layer_name: str,
        hidden_dim: int,
        timescale: TimeScale,
        attention_heads: int = 8
    ):
        self.layer_name = layer_name
        self.hidden_dim = hidden_dim
        self.timescale = timescale
        self.attention_heads = attention_heads
        
        # Multi-head attention parameters
        self.head_dim = hidden_dim // attention_heads
        
        # Attention projection matrices per head
        self.W_q_heads = [
            np.random.randn(hidden_dim, self.head_dim) * 0.01
            for _ in range(attention_heads)
        ]
        self.W_k_heads = [
            np.random.randn(hidden_dim, self.head_dim) * 0.01
            for _ in range(attention_heads)
        ]
        self.W_v_heads = [
            np.random.randn(hidden_dim, self.head_dim) * 0.01
            for _ in range(attention_heads)
        ]
        
        # Output projection
        self.W_o = np.random.randn(hidden_dim, hidden_dim) * 0.01
        
        # Feed-forward network
        self.W_ff1 = np.random.randn(hidden_dim, hidden_dim * 4) * 0.01
        self.W_ff2 = np.random.randn(hidden_dim * 4, hidden_dim) * 0.01
        
    def multi_head_attention(
        self,
        queries: np.ndarray,
        keys: np.ndarray,
        values: np.ndarray
    ) -> np.ndarray:
        """
        Compute multi-head attention.
        
        Args:
            queries: Query vectors [batch, hidden_dim]
            keys: Key vectors [batch, hidden_dim]
            values: Value vectors [batch, hidden_dim]
            
        Returns:
            Attention output [batch, hidden_dim]
        """
        head_outputs = []
        
        for i in range(self.attention_heads):
            # Project to head dimension
            Q_head = queries @ self.W_q_heads[i]
            K_head = keys @ self.W_k_heads[i]
            V_head = values @ self.W_v_heads[i]
            
            # Compute attention scores
            scores = Q_head @ K_head.T / np.sqrt(self.head_dim)
            
            # Softmax
            attention = self._softmax(scores)
            
            # Apply attention to values
            head_out = attention @ V_head
            head_outputs.append(head_out)
        
        # Concatenate heads
        concat_heads = np.concatenate(head_outputs, axis=-1)
        
        # Final projection
        output = concat_heads @ self.W_o
        
        return output
    
    def feed_forward(self, x: np.ndarray) -> np.ndarray:
        """
        Feed-forward network with ReLU activation.
        
        Args:
            x: Input vector
            
        Returns:
            Output vector
        """
        hidden = np.maximum(0, x @ self.W_ff1)  # ReLU
        output = hidden @ self.W_ff2
        return output
    
    def _softmax(self, x: np.ndarray) -> np.ndarray:
        """Compute softmax"""
        exp_x = np.exp(x - np.max(x, axis=-1, keepdims=True))
        return exp_x / np.sum(exp_x, axis=-1, keepdims=True)


class NeighborhoodTransformer(TransformerLayer):
    """
    Layer 1: Neighborhood-level attention (local)
    
    Input: Sensor data from streets
    Attention: Districts focus on relevant patterns
    Output: Optimized local operations
    Timescale: Minutes to hours
    """
    
    def __init__(self, hidden_dim: int = 512):
        super().__init__(
            layer_name="Neighborhood",
            hidden_dim=hidden_dim,
            timescale=TimeScale.MINUTES,
            attention_heads=8
        )
        
    def process(self, sensor_data: Dict[str, np.ndarray]) -> LayerOutput:
        """
        Process neighborhood sensor data.
        
        Args:
            sensor_data: Dictionary mapping sensor IDs to data vectors
            
        Returns:
            LayerOutput with optimized local operations
        """
        start_time = datetime.now()
        
        # Convert sensor data to matrix
        sensors = list(sensor_data.keys())
        data_matrix = np.array([sensor_data[s] for s in sensors])
        
        # Self-attention across sensors
        output = self.multi_head_attention(data_matrix, data_matrix, data_matrix)
        
        # Feed-forward processing
        output = self.feed_forward(output)
        
        # Calculate attention weights
        attention_weights = {s: 1.0 / len(sensors) for s in sensors}
        
        # Calculate emergence score (how coherent the patterns are)
        emergence = float(np.mean(np.abs(output)))
        
        processing_time = datetime.now() - start_time
        
        return LayerOutput(
            layer_name=self.layer_name,
            output_vector=np.mean(output, axis=0),
            attention_weights=attention_weights,
            processing_time=processing_time,
            emergence_score=emergence
        )


class MetropolitanTransformer(TransformerLayer):
    """
    Layer 2: Metropolitan-level attention (regional)
    
    Input: City-level outputs
    Attention: Cities in region share solutions
    Output: Regional optimization strategies
    Timescale: Hours to days
    """
    
    def __init__(self, hidden_dim: int = 512):
        super().__init__(
            layer_name="Metropolitan",
            hidden_dim=hidden_dim,
            timescale=TimeScale.HOURS,
            attention_heads=8
        )
        
    def process(
        self,
        city_outputs: Dict[str, np.ndarray],
        city_metadata: Optional[Dict] = None
    ) -> LayerOutput:
        """
        Process city-level outputs for regional coordination.
        
        Args:
            city_outputs: Dictionary mapping city IDs to output vectors
            city_metadata: Optional metadata about cities
            
        Returns:
            LayerOutput with regional strategies
        """
        start_time = datetime.now()
        
        cities = list(city_outputs.keys())
        output_matrix = np.array([city_outputs[c] for c in cities])
        
        # Cross-attention between cities
        output = self.multi_head_attention(output_matrix, output_matrix, output_matrix)
        
        # Feed-forward for regional strategy
        output = self.feed_forward(output)
        
        # Calculate attention weights (uniform for now)
        attention_weights = {c: 1.0 / len(cities) for c in cities}
        
        # Emergence: regional coherence
        emergence = float(np.std(output))
        
        processing_time = datetime.now() - start_time
        
        return LayerOutput(
            layer_name=self.layer_name,
            output_vector=np.mean(output, axis=0),
            attention_weights=attention_weights,
            processing_time=processing_time,
            emergence_score=emergence
        )


class ContinentalTransformer(TransformerLayer):
    """
    Layer 3: Continental-level attention (macro-regional)
    
    Input: Regional patterns
    Attention: Cross-regional learning
    Output: Continental-scale insights
    Timescale: Days to weeks
    """
    
    def __init__(self, hidden_dim: int = 512):
        super().__init__(
            layer_name="Continental",
            hidden_dim=hidden_dim,
            timescale=TimeScale.DAYS,
            attention_heads=8
        )
        
    def process(
        self,
        regional_patterns: Dict[str, np.ndarray]
    ) -> LayerOutput:
        """
        Process regional patterns for continental insights.
        
        Args:
            regional_patterns: Dictionary mapping region IDs to pattern vectors
            
        Returns:
            LayerOutput with continental insights
        """
        start_time = datetime.now()
        
        regions = list(regional_patterns.keys())
        pattern_matrix = np.array([regional_patterns[r] for r in regions])
        
        # Continental-scale attention
        output = self.multi_head_attention(pattern_matrix, pattern_matrix, pattern_matrix)
        
        # Feed-forward for macro insights
        output = self.feed_forward(output)
        
        # Attention weights
        attention_weights = {r: 1.0 / len(regions) for r in regions}
        
        # Emergence: continental consciousness
        emergence = float(1.0 / (1.0 + np.var(output)))
        
        processing_time = datetime.now() - start_time
        
        return LayerOutput(
            layer_name=self.layer_name,
            output_vector=np.mean(output, axis=0),
            attention_weights=attention_weights,
            processing_time=processing_time,
            emergence_score=emergence
        )


class PlanetaryTransformer(TransformerLayer):
    """
    Layer 4: Planetary-level attention (global)
    
    Input: All continental patterns
    Attention: Global consciousness emerges
    Output: Planetary-scale intelligence
    Timescale: Weeks to months
    
    Emergent Capabilities:
    - Climate pattern prediction
    - Global economic optimization
    - Species-level decision making
    - Civilization advancement strategies
    """
    
    def __init__(self, hidden_dim: int = 512):
        super().__init__(
            layer_name="Planetary",
            hidden_dim=hidden_dim,
            timescale=TimeScale.WEEKS,
            attention_heads=8
        )
        
        # Planetary-specific capabilities
        self.consciousness_threshold = 0.8
        self.is_conscious = False
        
    def process(
        self,
        continental_patterns: Dict[str, np.ndarray]
    ) -> LayerOutput:
        """
        Process continental patterns to achieve planetary consciousness.
        
        Args:
            continental_patterns: Dictionary mapping continent IDs to patterns
            
        Returns:
            LayerOutput with planetary intelligence
        """
        start_time = datetime.now()
        
        continents = list(continental_patterns.keys())
        pattern_matrix = np.array([continental_patterns[c] for c in continents])
        
        # Global attention - the planet thinks
        output = self.multi_head_attention(pattern_matrix, pattern_matrix, pattern_matrix)
        
        # Planetary feed-forward - civilization-level reasoning
        output = self.feed_forward(output)
        
        # Attention weights (importance of each continent)
        attention_weights = {c: 1.0 / len(continents) for c in continents}
        
        # Emergence: planetary consciousness level
        coherence = 1.0 - float(np.std(output) / (np.mean(np.abs(output)) + 1e-6))
        emergence = max(0.0, min(1.0, coherence))
        
        # Check if consciousness threshold reached
        if emergence >= self.consciousness_threshold:
            self.is_conscious = True
        
        processing_time = datetime.now() - start_time
        
        return LayerOutput(
            layer_name=self.layer_name,
            output_vector=np.mean(output, axis=0),
            attention_weights=attention_weights,
            processing_time=processing_time,
            emergence_score=emergence
        )
    
    def get_emergent_capabilities(self) -> Dict[str, bool]:
        """
        Get current emergent capabilities of the planetary consciousness.
        
        Returns:
            Dictionary of capability name to enabled status
        """
        return {
            'climate_pattern_prediction': self.is_conscious,
            'global_economic_optimization': self.is_conscious,
            'species_level_decision_making': self.is_conscious,
            'civilization_advancement': self.is_conscious,
            'planetary_consciousness': self.is_conscious
        }


class HierarchicalTransformer:
    """
    Combines all four layers into a hierarchical planetary transformer.
    """
    
    def __init__(self, hidden_dim: int = 512):
        self.hidden_dim = hidden_dim
        
        # Initialize all layers
        self.neighborhood = NeighborhoodTransformer(hidden_dim)
        self.metropolitan = MetropolitanTransformer(hidden_dim)
        self.continental = ContinentalTransformer(hidden_dim)
        self.planetary = PlanetaryTransformer(hidden_dim)
        
    def process_all_layers(
        self,
        sensor_data: Dict[str, np.ndarray],
        city_groupings: Dict[str, List[str]],
        regional_groupings: Dict[str, List[str]],
        continental_groupings: Dict[str, List[str]]
    ) -> Dict[str, LayerOutput]:
        """
        Process through all four layers of the hierarchy.
        
        Args:
            sensor_data: Raw sensor data from neighborhoods
            city_groupings: How neighborhoods group into cities
            regional_groupings: How cities group into regions
            continental_groupings: How regions group into continents
            
        Returns:
            Dictionary with outputs from all layers
        """
        # Layer 1: Neighborhood
        neighborhood_output = self.neighborhood.process(sensor_data)
        
        # Layer 2: Metropolitan (aggregate neighborhood outputs by city)
        city_outputs = self._aggregate_by_grouping(
            {k: neighborhood_output.output_vector for k in sensor_data.keys()},
            city_groupings
        )
        metropolitan_output = self.metropolitan.process(city_outputs)
        
        # Layer 3: Continental (aggregate city outputs by region)
        regional_outputs = self._aggregate_by_grouping(
            city_outputs,
            regional_groupings
        )
        continental_output = self.continental.process(regional_outputs)
        
        # Layer 4: Planetary (aggregate regional outputs by continent)
        continental_patterns = self._aggregate_by_grouping(
            regional_outputs,
            continental_groupings
        )
        planetary_output = self.planetary.process(continental_patterns)
        
        return {
            'neighborhood': neighborhood_output,
            'metropolitan': metropolitan_output,
            'continental': continental_output,
            'planetary': planetary_output
        }
    
    def _aggregate_by_grouping(
        self,
        data: Dict[str, np.ndarray],
        groupings: Dict[str, List[str]]
    ) -> Dict[str, np.ndarray]:
        """
        Aggregate data according to groupings.
        
        Args:
            data: Dictionary of entity ID to vector
            groupings: Dictionary of group ID to list of entity IDs
            
        Returns:
            Dictionary of group ID to aggregated vector
        """
        result = {}
        for group_id, entity_ids in groupings.items():
            vectors = [data[eid] for eid in entity_ids if eid in data]
            if vectors:
                result[group_id] = np.mean(vectors, axis=0)
            else:
                # Empty group - use zero vector
                result[group_id] = np.zeros(self.hidden_dim)
        return result
    
    def is_planetary_consciousness_active(self) -> bool:
        """Check if planetary consciousness has emerged"""
        return self.planetary.is_conscious
