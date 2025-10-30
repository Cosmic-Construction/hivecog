"""
Unit tests for EconomicBackpropagation
"""

import sys
import os
import unittest
import numpy as np

# Add parent directory to path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../..'))

from planetary_transformer.core import CityAsAttentionHead, EconomicBackpropagation


class TestEconomicBackpropagation(unittest.TestCase):
    """Test cases for EconomicBackpropagation"""
    
    def setUp(self):
        """Set up test fixtures"""
        self.economics = EconomicBackpropagation(
            learning_rate=0.01,
            reputation_rate=0.05,
            decay_rate=0.95,
            survival_threshold=1000.0
        )
        
        self.cities = [
            CityAsAttentionHead("City1", "spec1", initial_budget=5000.0),
            CityAsAttentionHead("City2", "spec2", initial_budget=4000.0),
            CityAsAttentionHead("City3", "spec3", initial_budget=3000.0),
        ]
    
    def test_backward_pass(self):
        """Test economic gradient backward pass"""
        value_created = 10000.0
        contributing = [self.cities[0], self.cities[1]]
        non_contributing = [self.cities[2]]
        
        initial_budgets = [city.budget for city in self.cities]
        initial_reputations = [city.reputation for city in self.cities]
        
        gradients = self.economics.backward_pass(
            value_created=value_created,
            contributing_cities=contributing,
            non_contributing=non_contributing,
            problem_solution={'id': 'test', 'success': True}
        )
        
        # Contributing cities should have positive gradients
        self.assertGreater(gradients[self.cities[0].city], 0)
        self.assertGreater(gradients[self.cities[1].city], 0)
        
        # Non-contributing cities should have negative gradients
        self.assertLess(gradients[self.cities[2].city], 0)
        
        # Budgets should have changed
        self.assertGreater(self.cities[0].budget, initial_budgets[0])
        self.assertGreater(self.cities[1].budget, initial_budgets[1])
        self.assertLess(self.cities[2].budget, initial_budgets[2])
        
        # Reputations should have changed
        self.assertGreater(self.cities[0].reputation, initial_reputations[0])
        self.assertGreater(self.cities[1].reputation, initial_reputations[1])
        self.assertLess(self.cities[2].reputation, initial_reputations[2])
    
    def test_calculate_contribution(self):
        """Test contribution calculation"""
        city = self.cities[0]
        value_created = 1000.0
        
        contribution = self.economics.calculate_contribution(city, value_created)
        
        self.assertGreater(contribution, 0)
        self.assertLessEqual(contribution, value_created)
    
    def test_evolutionary_pressure(self):
        """Test evolutionary pressure and selection"""
        # Create cities with varying budgets
        high_budget = CityAsAttentionHead("Rich", "spec1", initial_budget=10000.0)
        low_budget = CityAsAttentionHead("Poor", "spec2", initial_budget=500.0)
        
        all_cities = [high_budget, low_budget]
        
        survivors = self.economics.evolutionary_pressure(all_cities, current_generation=1)
        
        # Rich city should survive
        city_names = [city.city for city in survivors]
        self.assertIn("Rich", city_names)
        
        # Poor city might not survive (below threshold)
        # But it's not deterministic, so we just check the function runs
        self.assertIsInstance(survivors, list)
    
    def test_spawn_variant(self):
        """Test spawning city variants"""
        parent = self.cities[0]
        parent.budget = 15000.0
        
        variant = self.economics.spawn_variant(parent, generation=1)
        
        # Variant should have related name
        self.assertIn(parent.city, variant.city)
        
        # Variant should have some of parent's budget
        self.assertGreater(variant.budget, 0)
        self.assertLess(variant.budget, parent.budget)
        
        # Variant should have inherited reputation
        self.assertGreater(variant.reputation, 0)
    
    def test_calculate_fitness(self):
        """Test fitness calculation"""
        city = self.cities[0]
        
        fitness = self.economics.calculate_fitness(city)
        
        self.assertGreater(fitness, 0)
        self.assertIsInstance(fitness, float)
    
    def test_get_top_performers(self):
        """Test getting top performing cities"""
        # Give different budgets and reputations
        self.cities[0].budget = 10000.0
        self.cities[1].budget = 5000.0
        self.cities[2].budget = 2000.0
        
        top_cities = self.economics.get_top_performers(self.cities, top_k=2)
        
        self.assertEqual(len(top_cities), 2)
        # First should be highest performer
        self.assertEqual(top_cities[0].city, "City1")
    
    def test_analyze_contribution_patterns(self):
        """Test contribution pattern analysis"""
        # Add some contributions
        value_created = 5000.0
        self.economics.backward_pass(
            value_created=value_created,
            contributing_cities=[self.cities[0], self.cities[1]],
            non_contributing=[self.cities[2]],
            problem_solution={'id': 'test1', 'success': True}
        )
        
        analysis = self.economics.analyze_contribution_patterns()
        
        self.assertIn('total_contributions', analysis)
        self.assertIn('total_value_created', analysis)
        self.assertIn('avg_contribution', analysis)
        self.assertIn('top_contributors', analysis)
        
        self.assertGreater(analysis['total_contributions'], 0)


if __name__ == '__main__':
    unittest.main()
