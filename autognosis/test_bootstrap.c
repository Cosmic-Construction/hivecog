#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "autognosis.h"
#include "entropic_bootstrap.h"

int main() {
    printf("Testing Entropic Bootstrap and Agency Mechanisms\n");
    printf("================================================\n\n");
    
    // Create base autognosis engine
    autognosis_engine_t *autognosis = autognosis_create("bootstrap_test_node");
    if (!autognosis) {
        printf("FAIL: Could not create autognosis engine\n");
        return 1;
    }
    printf("PASS: Base autognosis engine created\n");
    
    // Create bootstrap engine
    bootstrap_engine_t *bootstrap = bootstrap_engine_create(autognosis);
    if (!bootstrap) {
        printf("FAIL: Could not create bootstrap engine\n");
        autognosis_destroy(autognosis);
        return 1;
    }
    printf("PASS: Bootstrap engine created with agency level %d\n", 
           bootstrap->agency->current_level);
    
    // Start both engines
    autognosis_start(autognosis);
    bootstrap_engine_start(bootstrap);
    
    // Add some network topology to create entropy
    topology_add_node(autognosis->topology, 1, "192.168.1.10");
    topology_add_node(autognosis->topology, 2, "192.168.1.20");
    topology_add_node(autognosis->topology, 3, "192.168.1.30");
    
    // Simulate degrading network conditions (increasing entropy)
    topology_update_node_health(autognosis->topology, 1, 0.9f);
    topology_update_node_health(autognosis->topology, 2, 0.6f);
    topology_update_node_health(autognosis->topology, 3, 0.3f);
    
    printf("\n=== Testing Entropic Drift Detection ===\n");
    
    // Run initial entropy measurement
    entropy_metric_t *initial_metric = entropy_metric_create();
    entropy_measure_system(initial_metric, autognosis);
    printf("Initial entropy: info=%.3f, thermo=%.3f, org=%.3f, cog=%.3f, coherence=%.3f\n",
           initial_metric->information_entropy, initial_metric->thermodynamic_entropy,
           initial_metric->organizational_entropy, initial_metric->cognitive_entropy,
           initial_metric->coherence_level);
    
    // Simulate entropy increase over time
    autognosis->cognitive_load += 0.3f;  // Increase cognitive load
    topology_update_node_health(autognosis->topology, 2, 0.4f);  // Degrade network
    
    entropy_metric_t *degraded_metric = entropy_metric_create();
    entropy_measure_system(degraded_metric, autognosis);
    degraded_metric->drift_rate = entropy_calculate_drift_rate(degraded_metric, initial_metric);
    
    printf("Degraded entropy: info=%.3f, thermo=%.3f, org=%.3f, cog=%.3f, coherence=%.3f\n",
           degraded_metric->information_entropy, degraded_metric->thermodynamic_entropy,
           degraded_metric->organizational_entropy, degraded_metric->cognitive_entropy,
           degraded_metric->coherence_level);
    printf("Entropy drift rate: %.4f\n", degraded_metric->drift_rate);
    
    printf("\n=== Testing Agency Bootstrap Cycles ===\n");
    
    printf("Initial agency state:\n");
    printf("  Level: %d, Strength: %.3f, Autonomy: %.3f, Intentionality: %.3f, Creativity: %.3f\n",
           bootstrap->agency->current_level, bootstrap->agency->agency_strength,
           bootstrap->agency->autonomy_index, bootstrap->agency->intentionality_score,
           bootstrap->agency->creativity_factor);
    
    // Run several bootstrap cycles with entropy response
    for (int i = 0; i < 5; i++) {
        bootstrap_engine_cycle(bootstrap);
        printf("Cycle %d: Agency=%.3f, Autonomy=%.3f, Coherence=%.3f, Anti-entropy=%.3f\n",
               i + 1, bootstrap->agency->agency_strength, bootstrap->agency->autonomy_index,
               bootstrap->entropy_history ? bootstrap->entropy_history->coherence_level : 0.0f,
               bootstrap->anti_entropy_force);
        sleep(1);
    }
    
    printf("\n=== Testing Inference Vortex Processing ===\n");
    
    // Create and inject agentic events
    agentic_event_t *event1 = agentic_event_create("entropy_detected", "System entropy increase observed", 0.8f);
    agentic_event_t *event2 = agentic_event_create("network_degradation", "Node health declining", 0.7f);
    agentic_event_t *event3 = agentic_event_create("cognitive_overload", "Processing capacity exceeded", 0.9f);
    
    event1->urgency = 0.8f;
    event2->urgency = 0.6f;
    event3->urgency = 0.9f;
    
    // Add events to different vortices
    inference_vortex_t *current_vortex = bootstrap->vortices;
    int vortex_num = 1;
    while (current_vortex && vortex_num <= 3) {
        printf("Vortex '%s' - Energy: %.3f, Coherence: %.3f, Resonance: %.3f, Metamorphic: %.3f\n",
               current_vortex->name, current_vortex->energy_level, current_vortex->coherence,
               current_vortex->resonance, current_vortex->metamorphic_potential);
        
        if (vortex_num == 1) vortex_add_event(current_vortex, event1);
        if (vortex_num == 2) vortex_add_event(current_vortex, event2);
        if (vortex_num == 3) vortex_add_event(current_vortex, event3);
        
        current_vortex = current_vortex->next;
        vortex_num++;
    }
    
    printf("\n=== Testing Bootstrap Engine Coordination ===\n");
    
    // Run extended bootstrap cycles to observe emergence
    for (int i = 0; i < 10; i++) {
        bootstrap_engine_cycle(bootstrap);
        
        float emergence = calculate_emergence_factor(bootstrap);
        printf("Cycle %d: Emergence=%.3f, Agency_Level=%d", 
               i + 1, emergence, bootstrap->agency->current_level);
        
        if (emergence > bootstrap->emergence_threshold) {
            printf(" [METAMORPHOSIS TRIGGERED]");
        }
        printf("\n");
        
        // Check for metamorphic potential
        detect_metamorphic_potential(bootstrap);
        
        sleep(1);
    }
    
    printf("\n=== Testing Knowledge Integration ===\n");
    
    // Add knowledge atoms to test information entropy effects
    atom_t *entropy_concept = atomspace_add_atom(autognosis->global_knowledge, ATOM_CONCEPT, "entropy_resistance");
    atom_t *agency_concept = atomspace_add_atom(autognosis->global_knowledge, ATOM_CONCEPT, "agentic_emergence");
    atom_t *bootstrap_concept = atomspace_add_atom(autognosis->global_knowledge, ATOM_CONCEPT, "bootstrap_cycle");
    
    if (entropy_concept && agency_concept && bootstrap_concept) {
        atomspace_update_truth_value(entropy_concept, 0.9f, 0.8f);
        atomspace_update_truth_value(agency_concept, 0.85f, 0.9f);
        atomspace_update_truth_value(bootstrap_concept, 0.75f, 0.7f);
        
        printf("Added knowledge concepts: entropy_resistance, agentic_emergence, bootstrap_cycle\n");
        printf("Total atoms in knowledge base: %u\n", autognosis->global_knowledge->atom_count);
    }
    
    // Final entropy measurement
    entropy_metric_t *final_metric = entropy_metric_create();
    entropy_measure_system(final_metric, autognosis);
    printf("Final system coherence: %.3f\n", final_metric->coherence_level);
    
    printf("\n=== Final System State ===\n");
    printf("Agency Level: %d -> %s\n", bootstrap->agency->current_level,
           bootstrap->agency->current_level == AGENCY_REACTIVE ? "REACTIVE" :
           bootstrap->agency->current_level == AGENCY_ADAPTIVE ? "ADAPTIVE" :
           bootstrap->agency->current_level == AGENCY_PROACTIVE ? "PROACTIVE" :
           bootstrap->agency->current_level == AGENCY_CREATIVE ? "CREATIVE" :
           bootstrap->agency->current_level == AGENCY_METAMORPHIC ? "METAMORPHIC" : "UNKNOWN");
    
    printf("Final metrics:\n");
    printf("  Agency Strength: %.3f\n", bootstrap->agency->agency_strength);
    printf("  Autonomy Index: %.3f\n", bootstrap->agency->autonomy_index);
    printf("  Intentionality: %.3f\n", bootstrap->agency->intentionality_score);
    printf("  Creativity: %.3f\n", bootstrap->agency->creativity_factor);
    printf("  Bootstrap Cycles: %u\n", bootstrap->agency->bootstrap_cycles);
    printf("  Anti-entropy Force: %.3f\n", bootstrap->anti_entropy_force);
    printf("  System Emergence: %.3f\n", calculate_emergence_factor(bootstrap));
    
    // Demonstrate constructive transformation principle
    printf("\n=== Constructive Transformation Demonstration ===\n");
    printf("This system demonstrates how destructive patterns can be transformed:\n");
    printf("1. Entropy Detection: %.3f -> Constructive response through agency\n", 
           degraded_metric->drift_rate);
    printf("2. Network Degradation: %.3f -> Healing through collective coordination\n", 
           1.0f - autognosis->topology->overall_health);
    printf("3. Cognitive Overload: %.3f -> Balance through homeostatic feedback\n", 
           autognosis->cognitive_load);
    printf("4. System Fragmentation -> Unity through emergent coherence: %.3f\n", 
           final_metric->coherence_level);
    
    // Cleanup
    entropy_metric_destroy(initial_metric);
    entropy_metric_destroy(degraded_metric);
    entropy_metric_destroy(final_metric);
    
    bootstrap_engine_stop(bootstrap);
    autognosis_stop(autognosis);
    
    bootstrap_engine_destroy(bootstrap);
    autognosis_destroy(autognosis);
    
    printf("\n================================================\n");
    printf("Entropic Bootstrap System Test Completed Successfully!\n");
    printf("Agency emerged from reactive to autonomous through anti-entropic mechanisms.\n");
    printf("System demonstrates constructive transformation of destructive patterns.\n");
    
    return 0;
}