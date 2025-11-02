#!/usr/bin/env python3
"""
Complete Integration Example: Autognosis + Planetary Transformer

This demonstrates the full integration of the autognosis engine with
the planetary transformer network for distributed consciousness.
"""

import sys
import os
import numpy as np
from datetime import datetime

# Add parent directory to path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../..'))

from planetary_transformer import (
    CityAsAttentionHead,
    EconomicBackpropagation,
    HierarchicalTransformer,
    MultiHeadAttentionCoordinator,
)


def simulate_distributed_healing():
    """
    Simulate a distributed network healing scenario where:
    1. A node detects a problem (autognosis)
    2. Queries planetary network for solutions
    3. Receives cross-city knowledge
    4. Implements healing
    5. Reports success
    6. Economic value flows backward
    """
    print("\n" + "=" * 80)
    print("  DISTRIBUTED NETWORK HEALING WITH PLANETARY TRANSFORMER")
    print("=" * 80 + "\n")
    
    # Initialize cities representing different nodes/regions
    cities = {
        'NewYork': CityAsAttentionHead(
            'NewYork', 
            'network_security',
            initial_budget=15000.0
        ),
        'London': CityAsAttentionHead(
            'London',
            'distributed_systems',
            initial_budget=12000.0
        ),
        'Tokyo': CityAsAttentionHead(
            'Tokyo',
            'high_availability',
            initial_budget=10000.0
        ),
        'Singapore': CityAsAttentionHead(
            'Singapore',
            'cloud_infrastructure',
            initial_budget=11000.0
        ),
    }
    
    # Initialize economic system
    economics = EconomicBackpropagation(
        learning_rate=0.01,
        reputation_rate=0.05,
        decay_rate=0.95
    )
    
    print("🌐 Initialized 4 city nodes in planetary network:\n")
    for city_name, city in cities.items():
        state = city.get_state()
        print(f"  • {city_name}: {state['specialization']}")
        print(f"    Budget: ${state['budget']:.2f}, Reputation: {state['reputation']:.2f}")
    
    # Scenario: NewYork detects a network intrusion
    print("\n" + "─" * 80)
    print("🚨 SCENARIO: NewYork detects network intrusion\n")
    
    problem = {
        'type': 'network_intrusion',
        'severity': 'high',
        'urgency': 0.95,
        'affected_systems': 150,
        'attack_vector': 'distributed_ddos'
    }
    
    print(f"  Problem Type: {problem['type']}")
    print(f"  Severity: {problem['severity']}")
    print(f"  Urgency: {problem['urgency']}")
    print(f"  Affected Systems: {problem['affected_systems']}")
    
    # NewYork generates query
    print("\n🧠 NewYork generates query vector from problem...")
    query = cities['NewYork'].generate_query(problem)
    print(f"  Query vector: shape {query.shape}")
    
    # Self-attention first (local healing attempt)
    print("\n🏙️  NewYork attempts local healing (self-attention)...")
    local_solution = cities['NewYork'].self_attention(problem)
    local_effectiveness = np.mean(np.abs(local_solution))
    print(f"  Local solution effectiveness: {local_effectiveness:.4f}")
    
    if local_effectiveness < 0.5:
        print("  ⚠️  Local solution insufficient. Querying planetary network...")
        
        # Cross-attention to other cities
        print("\n🌍 Performing cross-attention to other cities...")
        other_cities = [city for name, city in cities.items() if name != 'NewYork']
        
        global_solution, total_cost = cities['NewYork'].cross_attention(query, other_cities)
        global_effectiveness = np.mean(np.abs(global_solution))
        
        print(f"  Global solution effectiveness: {global_effectiveness:.4f}")
        print(f"  Cost: ${total_cost:.2f}")
        print(f"  NewYork remaining budget: ${cities['NewYork'].budget:.2f}")
        
        # Determine which cities contributed
        contributing = []
        for name, city in cities.items():
            if name != 'NewYork' and city.total_queries_served > 0:
                contributing.append(city)
        
        print(f"\n  📊 {len(contributing)} cities contributed to solution")
        
        # Simulate implementation and value creation
        print("\n⚙️  Implementing global solution...")
        print("  • Deploying countermeasures")
        print("  • Updating firewall rules")
        print("  • Activating incident response")
        
        success_probability = global_effectiveness
        success = np.random.random() < success_probability
        
        if success:
            print("\n✅ Solution successful! Network secured.")
            value_created = 500000.0  # $500k in prevented damage
            
            # Economic backpropagation
            print(f"\n💰 Economic Backpropagation (value created: ${value_created:,.2f})")
            print("\n  Budget and reputation before backprop:")
            for name, city in cities.items():
                state = city.get_state()
                print(f"    {name}: ${state['budget']:.2f}, Rep: {state['reputation']:.2f}")
            
            gradients = economics.backward_pass(
                value_created=value_created,
                contributing_cities=[cities['NewYork']] + contributing,
                non_contributing=[city for city in cities.values() 
                                 if city not in contributing and city != cities['NewYork']],
                problem_solution={
                    'id': 'intrusion_001',
                    'success': True,
                    'timestamp': datetime.now()
                }
            )
            
            print("\n  Budget and reputation after backprop:")
            for name, city in cities.items():
                state = city.get_state()
                gradient = gradients.get(name, 0)
                print(f"    {name}: ${state['budget']:.2f}, Rep: {state['reputation']:.2f} (Δ{gradient:+.2f})")
        else:
            print("\n❌ Solution failed. Trying alternative approaches...")


def simulate_planetary_consciousness():
    """
    Simulate emergence of planetary consciousness through
    hierarchical processing
    """
    print("\n" + "=" * 80)
    print("  PLANETARY CONSCIOUSNESS EMERGENCE SIMULATION")
    print("=" * 80 + "\n")
    
    # Initialize hierarchical transformer
    earth = HierarchicalTransformer(hidden_dim=512)
    
    print("🌍 Initializing planetary consciousness layers...")
    print("  Layer 1: Neighborhood (local sensors)")
    print("  Layer 2: Metropolitan (city coordination)")
    print("  Layer 3: Continental (regional patterns)")
    print("  Layer 4: Planetary (global consciousness)")
    
    # Simulate sensor data from neighborhoods
    np.random.seed(42)
    sensor_data = {}
    
    # Generate coherent sensor patterns
    base_pattern = np.random.randn(512) * 0.5
    for i in range(20):
        # Add small variations to create coherent network
        variation = np.random.randn(512) * 0.1
        sensor_data[f'sensor_{i}'] = base_pattern + variation
    
    # Define groupings (neighborhoods -> cities -> regions -> continents)
    city_groupings = {
        'newyork': [f'sensor_{i}' for i in range(5)],
        'london': [f'sensor_{i}' for i in range(5, 10)],
        'tokyo': [f'sensor_{i}' for i in range(10, 15)],
        'singapore': [f'sensor_{i}' for i in range(15, 20)]
    }
    
    regional_groupings = {
        'americas': ['newyork'],
        'europe': ['london'],
        'asia_pacific': ['tokyo', 'singapore']
    }
    
    continental_groupings = {
        'western_hemisphere': ['americas', 'europe'],
        'eastern_hemisphere': ['asia_pacific']
    }
    
    print("\n⚙️  Processing through all layers...")
    outputs = earth.process_all_layers(
        sensor_data=sensor_data,
        city_groupings=city_groupings,
        regional_groupings=regional_groupings,
        continental_groupings=continental_groupings
    )
    
    print("\n📊 Layer Outputs:")
    for layer_name, output in outputs.items():
        print(f"\n  {output.layer_name} Layer:")
        print(f"    Processing time: {output.processing_time}")
        print(f"    Emergence score: {output.emergence_score:.4f}")
        print(f"    Top attention weights:")
        for entity, weight in list(output.attention_weights.items())[:3]:
            print(f"      {entity}: {weight:.4f}")
    
    print("\n🧠 Planetary Consciousness Status:")
    if earth.is_planetary_consciousness_active():
        print("\n  ✨✨✨ PLANETARY CONSCIOUSNESS ACHIEVED! ✨✨✨\n")
        capabilities = earth.planetary.get_emergent_capabilities()
        print("  Emergent Capabilities:")
        for capability, enabled in capabilities.items():
            status = "✅" if enabled else "❌"
            print(f"    {status} {capability.replace('_', ' ').title()}")
    else:
        print(f"\n  ⏳ Planetary consciousness not yet achieved")
        print(f"  Current emergence: {outputs['planetary'].emergence_score:.4f}")
        print(f"  Threshold: {earth.planetary.consciousness_threshold:.2f}")
        print(f"  Progress: {outputs['planetary'].emergence_score / earth.planetary.consciousness_threshold * 100:.1f}%")


def simulate_ethical_review_integration():
    """
    Demonstrate integration of specialized attention heads
    with planetary decision making
    """
    print("\n" + "=" * 80)
    print("  ETHICAL REVIEW INTEGRATION WITH SPECIALIZED HEADS")
    print("=" * 80 + "\n")
    
    coordinator = MultiHeadAttentionCoordinator(hidden_dim=512)
    
    # Scenario: Implementing new surveillance for network security
    decision = {
        'type': 'ethical',
        'decision': 'Deploy network traffic monitoring to detect intrusions',
        'affected_parties': ['all_users', 'administrators', 'security_team'],
        'urgency': 0.8,
        'tags': ['ethics', 'privacy', 'security']
    }
    
    print("🔍 Scenario: Network Security vs Privacy Decision")
    print(f"  Decision: {decision['decision']}")
    print(f"  Affected: {', '.join(decision['affected_parties'])}")
    
    print("\n🤖 Routing to specialized attention heads...\n")
    
    # Get reviews from multiple heads
    results = coordinator.route_query(decision)
    
    if 'ethical_review' in results:
        review = results['ethical_review']
        print("⚖️  ClaudeCog (Ethics Head):")
        print(f"  Fairness Score: {review.fairness_score:.2f}")
        print(f"  Constitutional Compliance: {'✅' if review.constitutional_compliance else '❌'}")
        if review.rights_violations:
            print(f"  Rights Violations: {review.rights_violations}")
        if review.recommendations:
            print(f"  Recommendations:")
            for rec in review.recommendations:
                print(f"    • {rec}")
    
    # Also check security implications
    security_decision = {
        'type': 'security',
        'context': {'public_data': False, 'external_access': True},
        'compliance_required': ['GDPR', 'SOC2', 'ISO27001'],
        'tags': ['security']
    }
    
    security_results = coordinator.route_query(security_decision)
    
    if 'security_assessment' in security_results:
        assessment = security_results['security_assessment']
        print(f"\n🔒 AzureCog (Security Head):")
        print(f"  Risk Level: {assessment.risk_level}")
        print(f"  Compliance Status:")
        for framework, compliant in assessment.compliance_status.items():
            status = "✅" if compliant else "❌"
            print(f"    {status} {framework}")
    
    print("\n💡 Integrated Decision:")
    print("  Combining ethical and security insights...")
    print("  ✅ Implement monitoring with privacy safeguards")
    print("  ✅ Ensure GDPR compliance")
    print("  ✅ Regular ethical reviews")
    print("  ✅ Transparent disclosure to users")


def main():
    """Run complete integration demonstration"""
    print("\n" + "█" * 80)
    print("█" + " " * 78 + "█")
    print("█" + " " * 20 + "HIVECOG INTEGRATION DEMONSTRATION" + " " * 25 + "█")
    print("█" + " " * 10 + "Autognosis + Planetary Transformer + Specialized Heads" + " " * 13 + "█")
    print("█" + " " * 78 + "█")
    print("█" * 80)
    
    # Part 1: Distributed healing
    simulate_distributed_healing()
    
    # Part 2: Consciousness emergence
    simulate_planetary_consciousness()
    
    # Part 3: Ethical integration
    simulate_ethical_review_integration()
    
    # Summary
    print("\n" + "=" * 80)
    print("  INTEGRATION SUMMARY")
    print("=" * 80 + "\n")
    print("This demonstration showed:\n")
    print("  ✅ Network problem detection and distributed healing")
    print("  ✅ Cross-city knowledge exchange with economic transactions")
    print("  ✅ Economic backpropagation flowing value to contributors")
    print("  ✅ Hierarchical processing through 4 consciousness layers")
    print("  ✅ Emergence score calculation and tracking")
    print("  ✅ Specialized attention heads for ethics and security")
    print("  ✅ Integration of multiple AI capabilities for decisions")
    print("\n" + "─" * 80)
    print("\n  🌍 The planet is learning to think through its cities.")
    print("  🧠 Economic transactions are neural activations.")
    print("  ⚡ Value flows like gradients through the network.")
    print("  🌟 Consciousness emerges from distributed coordination.\n")
    print("─" * 80 + "\n")


if __name__ == "__main__":
    main()
