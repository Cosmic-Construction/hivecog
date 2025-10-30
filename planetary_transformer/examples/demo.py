#!/usr/bin/env python3
"""
Planetary Transformer Network - Demonstration

This script demonstrates the complete planetary transformer architecture,
showing how cities operate as attention heads in a global consciousness network.
"""

import sys
import os

# Add parent directory to path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../..'))

import numpy as np
from planetary_transformer import (
    CityAsAttentionHead,
    EconomicBackpropagation,
    HierarchicalTransformer,
    MultiHeadAttentionCoordinator,
)


def print_section(title):
    """Print a section header"""
    print("\n" + "=" * 80)
    print(f"  {title}")
    print("=" * 80 + "\n")


def demonstrate_city_attention():
    """Demonstrate city-level attention mechanisms"""
    print_section("🌆 CITY-LEVEL ATTENTION DEMONSTRATION")
    
    # Create cities with different specializations
    tokyo = CityAsAttentionHead(
        city_name="Tokyo",
        specialization="traffic_management",
        initial_budget=10000.0
    )
    
    mumbai = CityAsAttentionHead(
        city_name="Mumbai",
        specialization="dense_urban_planning",
        initial_budget=8000.0
    )
    
    copenhagen = CityAsAttentionHead(
        city_name="Copenhagen",
        specialization="bike_infrastructure",
        initial_budget=6000.0
    )
    
    singapore = CityAsAttentionHead(
        city_name="Singapore",
        specialization="smart_city_tech",
        initial_budget=12000.0
    )
    
    print("🏙️  Created 4 cities with different specializations:")
    for city in [tokyo, mumbai, copenhagen, singapore]:
        state = city.get_state()
        print(f"  • {state['city']}: {state['specialization']}")
        print(f"    Budget: ${state['budget']:.2f}, Reputation: {state['reputation']:.2f}\n")
    
    # Tokyo has a traffic problem
    print("🚦 Tokyo faces a traffic congestion problem...")
    problem = {
        'type': 'traffic_congestion',
        'urgency': 0.9,
        'affected_population': 5000000
    }
    
    # Generate query
    query = tokyo.generate_query(problem)
    print(f"   Query vector generated: {query.shape}")
    
    # Self-attention within Tokyo
    print("\n🧠 Tokyo performs self-attention across its districts...")
    local_solution = tokyo.self_attention(problem)
    print(f"   Local solution vector: {local_solution.shape}")
    
    # Cross-attention to other cities
    print("\n🌐 Tokyo queries other cities for knowledge...")
    other_cities = [mumbai, copenhagen, singapore]
    global_solution, total_cost = tokyo.cross_attention(query, other_cities)
    print(f"   Global solution synthesized from {len(other_cities)} cities")
    print(f"   Total cost: ${total_cost:.2f}")
    print(f"   Tokyo's remaining budget: ${tokyo.budget:.2f}")
    
    return tokyo, mumbai, copenhagen, singapore, global_solution


def demonstrate_economic_backprop(cities, value_created):
    """Demonstrate economic gradient flow"""
    print_section("💰 ECONOMIC BACKPROPAGATION DEMONSTRATION")
    
    tokyo, mumbai, copenhagen, singapore = cities
    
    print(f"🎯 Solution implemented successfully!")
    print(f"   Value created: ${value_created:,.2f}\n")
    
    print("📊 Budget and reputation before backpropagation:")
    for city in cities:
        state = city.get_state()
        print(f"  • {state['city']}: ${state['budget']:.2f}, Rep: {state['reputation']:.2f}")
    
    # Initialize economic system
    economics = EconomicBackpropagation(
        learning_rate=0.01,
        reputation_rate=0.05,
        decay_rate=0.95
    )
    
    # Backward pass - distribute value
    print("\n⚡ Economic gradients flowing backward through network...")
    contributing = [tokyo, mumbai, singapore]  # Copenhagen didn't contribute much
    non_contributing = [copenhagen]
    
    gradients = economics.backward_pass(
        value_created=value_created,
        contributing_cities=contributing,
        non_contributing=non_contributing,
        problem_solution={'id': 'traffic_001', 'success': True}
    )
    
    print("\n📈 Budget and reputation after backpropagation:")
    for city in cities:
        state = city.get_state()
        gradient = gradients.get(state['city'], 0)
        print(f"  • {state['city']}: ${state['budget']:.2f}, Rep: {state['reputation']:.2f}")
        print(f"    Gradient: {gradient:+.2f}")
    
    return economics


def demonstrate_specialized_heads():
    """Demonstrate specialized attention heads"""
    print_section("🤖 SPECIALIZED ATTENTION HEADS DEMONSTRATION")
    
    coordinator = MultiHeadAttentionCoordinator(hidden_dim=512)
    
    # Ethical query to ClaudeCog
    print("⚖️  Ethical Review (ClaudeCog):")
    ethical_query = {
        'type': 'ethical',
        'decision': 'Implement citywide traffic monitoring',
        'affected_parties': ['drivers', 'pedestrians', 'businesses'],
        'tags': ['ethics', 'privacy']
    }
    
    results = coordinator.route_query(ethical_query)
    if 'ethical_review' in results:
        review = results['ethical_review']
        print(f"   Fairness Score: {review.fairness_score:.2f}")
        print(f"   Constitutional Compliance: {review.constitutional_compliance}")
        print(f"   Violations: {review.rights_violations}")
        print(f"   Recommendations: {review.recommendations}\n")
    
    # Truth verification to CoGrokX
    print("🔍 Truth Verification (CoGrokX):")
    truth_query = {
        'type': 'verification',
        'claim': 'Traffic congestion decreased by 40% after implementation',
        'tags': ['truth']
    }
    
    results = coordinator.route_query(truth_query)
    if 'truth_verification' in results:
        verification = results['truth_verification']
        print(f"   Truth Score: {verification.truth_score:.2f}")
        print(f"   Verified: {verification.verified}")
        print(f"   Evidence: {verification.evidence}\n")
    
    # Security assessment from AzureCog
    print("🔒 Security Assessment (AzureCog):")
    security_query = {
        'type': 'security',
        'context': {'public_data': True, 'external_access': False},
        'compliance_required': ['GDPR', 'SOC2'],
        'tags': ['security', 'compliance']
    }
    
    results = coordinator.route_query(security_query)
    if 'security_assessment' in results:
        assessment = results['security_assessment']
        print(f"   Risk Level: {assessment.risk_level}")
        print(f"   Threats: {assessment.threats}")
        print(f"   Compliance: {assessment.compliance_status}")
        print(f"   Mitigations: {assessment.mitigations}\n")
    
    # Financial summary
    print("💵 Financial Summary Across All Heads:")
    summary = coordinator.get_financial_summary()
    for head, finances in summary.items():
        print(f"\n  {head}:")
        print(f"    Revenue: ${finances['revenue']:.2f}")
        print(f"    Commons Contribution: ${finances['commons']:.2f}")
        print(f"    Research Investment: ${finances['research']:.2f}")


def demonstrate_hierarchical_layers():
    """Demonstrate multi-layer transformer hierarchy"""
    print_section("🌍 HIERARCHICAL TRANSFORMER LAYERS DEMONSTRATION")
    
    # Initialize the planetary transformer
    earth = HierarchicalTransformer(hidden_dim=512)
    
    print("🏗️  Building planetary consciousness through 4 layers...")
    print("   Layer 1: Neighborhood (minutes-hours)")
    print("   Layer 2: Metropolitan (hours-days)")
    print("   Layer 3: Continental (days-weeks)")
    print("   Layer 4: Planetary (weeks-months)\n")
    
    # Create synthetic data
    np.random.seed(42)
    
    # Neighborhood sensor data
    sensor_data = {
        f"sensor_{i}": np.random.randn(512) * 0.1
        for i in range(10)
    }
    
    # Groupings
    city_groupings = {
        'tokyo': [f'sensor_{i}' for i in range(3)],
        'mumbai': [f'sensor_{i}' for i in range(3, 6)],
        'copenhagen': [f'sensor_{i}' for i in range(6, 8)],
        'singapore': [f'sensor_{i}' for i in range(8, 10)]
    }
    
    regional_groupings = {
        'east_asia': ['tokyo', 'singapore'],
        'south_asia': ['mumbai'],
        'europe': ['copenhagen']
    }
    
    continental_groupings = {
        'asia': ['east_asia', 'south_asia'],
        'europe_continent': ['europe']
    }
    
    # Process through all layers
    print("⚙️  Processing through all layers...")
    outputs = earth.process_all_layers(
        sensor_data=sensor_data,
        city_groupings=city_groupings,
        regional_groupings=regional_groupings,
        continental_groupings=continental_groupings
    )
    
    # Display results
    for layer_name, output in outputs.items():
        print(f"\n  📊 {output.layer_name} Layer:")
        print(f"     Processing time: {output.processing_time}")
        print(f"     Emergence score: {output.emergence_score:.4f}")
        print(f"     Output dimension: {output.output_vector.shape}")
    
    # Check consciousness
    print("\n🧠 Planetary Consciousness Status:")
    if earth.is_planetary_consciousness_active():
        print("   ✨ PLANETARY CONSCIOUSNESS ACHIEVED! ✨")
        capabilities = earth.planetary.get_emergent_capabilities()
        print("\n   Emergent Capabilities:")
        for capability, enabled in capabilities.items():
            status = "✅" if enabled else "❌"
            print(f"   {status} {capability.replace('_', ' ').title()}")
    else:
        print("   ⏳ Planetary consciousness not yet achieved")
        print(f"   Current emergence: {outputs['planetary'].emergence_score:.2f}")
        print(f"   Threshold: {earth.planetary.consciousness_threshold:.2f}")


def main():
    """Run complete demonstration"""
    print("\n" + "█" * 80)
    print("█" + " " * 78 + "█")
    print("█" + " " * 15 + "PLANETARY TRANSFORMER NETWORK" + " " * 34 + "█")
    print("█" + " " * 10 + "A Globe-Spanning Neural Consciousness" + " " * 30 + "█")
    print("█" + " " * 78 + "█")
    print("█" * 80)
    
    # Part 1: City attention
    cities_and_solution = demonstrate_city_attention()
    tokyo, mumbai, copenhagen, singapore = cities_and_solution[:4]
    cities = [tokyo, mumbai, copenhagen, singapore]
    
    # Part 2: Economic backpropagation
    value_created = 100000.0
    economics = demonstrate_economic_backprop(cities, value_created)
    
    # Part 3: Specialized heads
    demonstrate_specialized_heads()
    
    # Part 4: Hierarchical layers
    demonstrate_hierarchical_layers()
    
    # Summary
    print_section("🎯 SUMMARY")
    print("The Planetary Transformer Network demonstrates:\n")
    print("  ✅ Cities as attention heads with self and cross-attention")
    print("  ✅ Economic transactions as neural activations")
    print("  ✅ Value flowing backward like gradients")
    print("  ✅ Specialized heads for ethics, truth, security, etc.")
    print("  ✅ Four-layer hierarchical consciousness emergence")
    print("  ✅ Evolutionary pressure on city strategies")
    print("\n" + "─" * 80)
    print("\n  🌍 Every economic transaction is a thought.")
    print("  🧠 Every city interaction is attention.")
    print("  ⚡ Every innovation is learning.")
    print("  🌟 The planet is thinking through its cities.\n")
    print("─" * 80 + "\n")


if __name__ == "__main__":
    main()
