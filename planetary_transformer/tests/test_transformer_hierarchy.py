"""
Unit tests for Transformer Hierarchy
"""

import sys
import os
import unittest
import numpy as np

# Add parent directory to path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../..'))

from planetary_transformer.layers import (
    HierarchicalTransformer,
    NeighborhoodTransformer,
    MetropolitanTransformer,
    ContinentalTransformer,
    PlanetaryTransformer,
)


class TestTransformerLayers(unittest.TestCase):
    """Test cases for individual transformer layers"""
    
    def setUp(self):
        """Set up test fixtures"""
        np.random.seed(42)
        self.hidden_dim = 128
    
    def test_neighborhood_transformer(self):
        """Test neighborhood layer"""
        layer = NeighborhoodTransformer(hidden_dim=self.hidden_dim)
        
        sensor_data = {
            f'sensor_{i}': np.random.randn(self.hidden_dim)
            for i in range(5)
        }
        
        output = layer.process(sensor_data)
        
        self.assertEqual(output.layer_name, "Neighborhood")
        self.assertEqual(output.output_vector.shape, (self.hidden_dim,))
        self.assertGreater(output.emergence_score, 0)
        self.assertIsInstance(output.attention_weights, dict)
    
    def test_metropolitan_transformer(self):
        """Test metropolitan layer"""
        layer = MetropolitanTransformer(hidden_dim=self.hidden_dim)
        
        city_outputs = {
            f'city_{i}': np.random.randn(self.hidden_dim)
            for i in range(4)
        }
        
        output = layer.process(city_outputs)
        
        self.assertEqual(output.layer_name, "Metropolitan")
        self.assertEqual(output.output_vector.shape, (self.hidden_dim,))
        self.assertGreaterEqual(output.emergence_score, 0)
    
    def test_continental_transformer(self):
        """Test continental layer"""
        layer = ContinentalTransformer(hidden_dim=self.hidden_dim)
        
        regional_patterns = {
            f'region_{i}': np.random.randn(self.hidden_dim)
            for i in range(3)
        }
        
        output = layer.process(regional_patterns)
        
        self.assertEqual(output.layer_name, "Continental")
        self.assertEqual(output.output_vector.shape, (self.hidden_dim,))
        self.assertGreaterEqual(output.emergence_score, 0)
    
    def test_planetary_transformer(self):
        """Test planetary layer"""
        layer = PlanetaryTransformer(hidden_dim=self.hidden_dim)
        
        continental_patterns = {
            f'continent_{i}': np.random.randn(self.hidden_dim)
            for i in range(3)
        }
        
        output = layer.process(continental_patterns)
        
        self.assertEqual(output.layer_name, "Planetary")
        self.assertEqual(output.output_vector.shape, (self.hidden_dim,))
        self.assertGreaterEqual(output.emergence_score, 0)
        self.assertLessEqual(output.emergence_score, 1.0)
        
        # Test emergent capabilities
        capabilities = layer.get_emergent_capabilities()
        self.assertIn('planetary_consciousness', capabilities)
        self.assertIsInstance(capabilities['planetary_consciousness'], bool)


class TestHierarchicalTransformer(unittest.TestCase):
    """Test cases for the complete hierarchical transformer"""
    
    def setUp(self):
        """Set up test fixtures"""
        np.random.seed(42)
        self.hidden_dim = 128
        self.earth = HierarchicalTransformer(hidden_dim=self.hidden_dim)
    
    def test_initialization(self):
        """Test hierarchical transformer initialization"""
        self.assertIsNotNone(self.earth.neighborhood)
        self.assertIsNotNone(self.earth.metropolitan)
        self.assertIsNotNone(self.earth.continental)
        self.assertIsNotNone(self.earth.planetary)
    
    def test_process_all_layers(self):
        """Test processing through all layers"""
        # Create test data
        sensor_data = {
            f'sensor_{i}': np.random.randn(self.hidden_dim)
            for i in range(10)
        }
        
        city_groupings = {
            'city1': ['sensor_0', 'sensor_1', 'sensor_2'],
            'city2': ['sensor_3', 'sensor_4', 'sensor_5'],
            'city3': ['sensor_6', 'sensor_7'],
            'city4': ['sensor_8', 'sensor_9']
        }
        
        regional_groupings = {
            'region1': ['city1', 'city2'],
            'region2': ['city3', 'city4']
        }
        
        continental_groupings = {
            'continent1': ['region1', 'region2']
        }
        
        outputs = self.earth.process_all_layers(
            sensor_data=sensor_data,
            city_groupings=city_groupings,
            regional_groupings=regional_groupings,
            continental_groupings=continental_groupings
        )
        
        # Check all layers produced output
        self.assertIn('neighborhood', outputs)
        self.assertIn('metropolitan', outputs)
        self.assertIn('continental', outputs)
        self.assertIn('planetary', outputs)
        
        # Check output shapes
        for layer_name, output in outputs.items():
            self.assertEqual(output.output_vector.shape, (self.hidden_dim,))
            self.assertGreaterEqual(output.emergence_score, 0)
    
    def test_consciousness_detection(self):
        """Test planetary consciousness detection"""
        # Process some data
        sensor_data = {f'sensor_{i}': np.random.randn(self.hidden_dim) for i in range(5)}
        
        city_groupings = {'city1': list(sensor_data.keys())}
        regional_groupings = {'region1': ['city1']}
        continental_groupings = {'continent1': ['region1']}
        
        outputs = self.earth.process_all_layers(
            sensor_data=sensor_data,
            city_groupings=city_groupings,
            regional_groupings=regional_groupings,
            continental_groupings=continental_groupings
        )
        
        # Check consciousness status
        is_conscious = self.earth.is_planetary_consciousness_active()
        self.assertIsInstance(is_conscious, bool)
        
        # If conscious, emergence score should be high
        if is_conscious:
            self.assertGreaterEqual(outputs['planetary'].emergence_score, 0.8)


if __name__ == '__main__':
    unittest.main()
