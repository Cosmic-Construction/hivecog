"""
Unit tests for CityAsAttentionHead
"""

import sys
import os
import unittest
import numpy as np

# Add parent directory to path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../..'))

from planetary_transformer.core import CityAsAttentionHead


class TestCityAsAttentionHead(unittest.TestCase):
    """Test cases for CityAsAttentionHead"""
    
    def setUp(self):
        """Set up test fixtures"""
        self.city = CityAsAttentionHead(
            city_name="TestCity",
            specialization="testing",
            hidden_dim=128,
            num_districts=4,
            initial_budget=5000.0,
            base_knowledge_price=10.0
        )
    
    def test_initialization(self):
        """Test city initialization"""
        self.assertEqual(self.city.city, "TestCity")
        self.assertEqual(self.city.specialization, "testing")
        self.assertEqual(self.city.hidden_dim, 128)
        self.assertEqual(self.city.num_districts, 4)
        self.assertEqual(self.city.budget, 5000.0)
        self.assertEqual(self.city.reputation, 1.0)
        self.assertEqual(len(self.city.local_neurons), 4)
    
    def test_generate_query(self):
        """Test query generation"""
        problem = {
            'type': 'traffic',
            'urgency': 0.8
        }
        query = self.city.generate_query(problem)
        
        self.assertEqual(query.shape, (128,))
        self.assertIsInstance(query, np.ndarray)
    
    def test_self_attention(self):
        """Test self-attention mechanism"""
        problem = {'type': 'test_problem'}
        solution = self.city.self_attention(problem)
        
        self.assertEqual(solution.shape, (128,))
        self.assertIsInstance(solution, np.ndarray)
    
    def test_cross_attention(self):
        """Test cross-attention to other cities"""
        other_city = CityAsAttentionHead(
            city_name="OtherCity",
            specialization="other",
            hidden_dim=128,
            initial_budget=3000.0
        )
        
        query = self.city.generate_query({'type': 'help'})
        solution, cost = self.city.cross_attention(query, [other_city])
        
        self.assertEqual(solution.shape, (128,))
        self.assertIsInstance(cost, float)
        self.assertGreaterEqual(cost, 0)
    
    def test_can_afford(self):
        """Test budget checking"""
        self.assertTrue(self.city.can_afford(100.0))
        self.assertTrue(self.city.can_afford(5000.0))
        self.assertFalse(self.city.can_afford(5001.0))
    
    def test_payment(self):
        """Test payment transfer"""
        recipient = CityAsAttentionHead(
            city_name="Recipient",
            specialization="receiver",
            hidden_dim=128
        )
        
        initial_budget = self.city.budget
        recipient_initial = recipient.budget
        amount = 100.0
        
        self.city.pay(recipient, amount)
        
        self.assertEqual(self.city.budget, initial_budget - amount)
        self.assertEqual(recipient.budget, recipient_initial + amount)
    
    def test_reputation_update(self):
        """Test reputation updates"""
        # Start with low reputation
        self.city.reputation = 0.5
        initial_reputation = self.city.reputation
        
        # Positive feedback should increase reputation
        self.city.update_reputation(0.9)
        self.assertGreater(self.city.reputation, initial_reputation)
        
        # Negative feedback should decrease reputation
        current_reputation = self.city.reputation
        self.city.update_reputation(0.1)
        self.assertLess(self.city.reputation, current_reputation)
    
    def test_get_state(self):
        """Test state retrieval"""
        state = self.city.get_state()
        
        self.assertIn('city', state)
        self.assertIn('specialization', state)
        self.assertIn('budget', state)
        self.assertIn('reputation', state)
        self.assertEqual(state['city'], 'TestCity')
        self.assertEqual(state['specialization'], 'testing')


class TestEconomicInteractions(unittest.TestCase):
    """Test economic interactions between cities"""
    
    def setUp(self):
        """Set up test fixtures"""
        self.tokyo = CityAsAttentionHead(
            city_name="Tokyo",
            specialization="traffic",
            hidden_dim=128,
            initial_budget=10000.0
        )
        
        self.mumbai = CityAsAttentionHead(
            city_name="Mumbai",
            specialization="density",
            hidden_dim=128,
            initial_budget=8000.0
        )
    
    def test_knowledge_exchange(self):
        """Test knowledge exchange between cities"""
        query = self.tokyo.generate_query({'type': 'traffic'})
        initial_tokyo_budget = self.tokyo.budget
        initial_mumbai_budget = self.mumbai.budget
        
        solution, cost = self.tokyo.cross_attention(query, [self.mumbai])
        
        # Tokyo should have paid
        self.assertLessEqual(self.tokyo.budget, initial_tokyo_budget)
        
        # Mumbai should have received payment (if relevant)
        # (Depends on relevance score and affordability)
        
        # Solution should be returned
        self.assertEqual(solution.shape, (128,))
    
    def test_multiple_city_attention(self):
        """Test attention across multiple cities"""
        copenhagen = CityAsAttentionHead(
            city_name="Copenhagen",
            specialization="bikes",
            hidden_dim=128,
            initial_budget=6000.0
        )
        
        query = self.tokyo.generate_query({'type': 'transport'})
        other_cities = [self.mumbai, copenhagen]
        
        solution, cost = self.tokyo.cross_attention(query, other_cities)
        
        self.assertEqual(solution.shape, (128,))
        self.assertGreaterEqual(cost, 0)


if __name__ == '__main__':
    unittest.main()
