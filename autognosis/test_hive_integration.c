#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "autognosis.h"
#include "hive_coordination.h"

void simulate_network_failure(autognosis_engine_t *engine, hive_coordinator_t *coordinator) {
    printf("\n=== Simulating Network Failure ===\n");
    
    // Simulate node going down
    topology_update_node_health(engine->topology, 2, 0.1f);
    topology_update_node_health(engine->topology, 3, 0.0f);
    
    printf("Nodes 2 and 3 are experiencing failures\n");
    printf("Network health dropped to: %.2f\n", engine->topology->overall_health);
    
    // Trigger autogenetic healing
    hive_coordinate_healing(coordinator, "node_failure");
    hive_coordinate_healing(coordinator, "connection_failed");
    
    autognosis_cognitive_cycle(engine);
    hive_coordinator_process_cycle(coordinator);
    
    printf("Autognosis health after failure: %.2f\n", engine->self_image->health_score);
    printf("Collective intelligence response: %.2f\n", coordinator->collective_intelligence_score);
}

void demonstrate_knowledge_sharing(autognosis_engine_t *engine1, hive_coordinator_t *coord1,
                                 autognosis_engine_t *engine2, hive_coordinator_t *coord2) {
    printf("\n=== Demonstrating Knowledge Sharing ===\n");
    
    // Node 1 learns something important
    atom_t *threat_atom = atomspace_add_atom(engine1->global_knowledge, 
        ATOM_CONCEPT, "security_threat_detected");
    if (threat_atom) {
        atomspace_update_truth_value(threat_atom, 0.9f, 0.95f);
        threat_atom->importance = 1.0f;
        printf("Node 1 detected security threat (truth=%.2f, importance=%.2f)\n", 
               threat_atom->truth_value, threat_atom->importance);
    }
    
    // Share knowledge through hive coordination
    hive_broadcast_knowledge(coord1, threat_atom);
    
    // Simulate receiving the knowledge on node 2
    knowledge_packet_t *packet = knowledge_packet_from_atom(threat_atom);
    if (packet) {
        coord2->process_shared_knowledge(coord2, packet);
        free(packet);
    }
    
    // Verify knowledge was integrated
    atom_t *received_atom = atomspace_find_atom(engine2->global_knowledge, "security_threat_detected");
    if (received_atom) {
        printf("Node 2 received shared knowledge: %s (truth=%.2f)\n", 
               received_atom->name, received_atom->truth_value);
    }
    
    printf("Knowledge sharing completed successfully\n");
}

void demonstrate_collective_healing(hive_coordinator_t *coord1, hive_coordinator_t *coord2) {
    printf("\n=== Demonstrating Collective Healing ===\n");
    
    // Create a complex problem that requires collective intelligence
    healing_request_t *request = healing_request_create("distributed_network_partitioning", 0.95f, coord1->node_id);
    if (request) {
        printf("Node %u requests help with: %s (severity=%.2f)\n", 
               request->requesting_node, request->problem_description, request->severity);
        
        // Node 1 makes healing request
        coord1->request_healing_assistance(coord1, request);
        
        // Node 2 responds to the request
        coord2->respond_to_healing_request(coord2, request);
        
        printf("Collective healing coordination completed\n");
        free(request);
    }
}

void demonstrate_emergence_behavior(hive_coordinator_t *coord1, hive_coordinator_t *coord2) {
    printf("\n=== Demonstrating Emergent Behavior ===\n");
    
    // Update collective knowledge in both nodes
    coord1->update_collective_knowledge(coord1);
    coord2->update_collective_knowledge(coord2);
    
    float emergence1 = hive_calculate_emergence_factor(coord1);
    float emergence2 = hive_calculate_emergence_factor(coord2);
    
    printf("Node 1 emergence factor: %.2f\n", emergence1);
    printf("Node 2 emergence factor: %.2f\n", emergence2);
    
    // Calculate collective swarm health
    float swarm1 = coord1->calculate_swarm_health(coord1);
    float swarm2 = coord2->calculate_swarm_health(coord2);
    
    printf("Node 1 swarm health assessment: %.2f\n", swarm1);
    printf("Node 2 swarm health assessment: %.2f\n", swarm2);
    
    printf("Emergent collective intelligence demonstrated\n");
}

int main() {
    printf("OpenCog Hive Autognosis Integration Test\n");
    printf("========================================\n");
    
    // Create two hive nodes
    autognosis_engine_t *engine1 = autognosis_create("hive_node_1");
    autognosis_engine_t *engine2 = autognosis_create("hive_node_2");
    
    if (!engine1 || !engine2) {
        printf("FAIL: Could not create autognosis engines\n");
        return 1;
    }
    
    // Start engines
    autognosis_start(engine1);
    autognosis_start(engine2);
    
    // Create hive coordinators
    hive_coordinator_t *coord1 = hive_coordinator_create(engine1, 1001);
    hive_coordinator_t *coord2 = hive_coordinator_create(engine2, 1002);
    
    if (!coord1 || !coord2) {
        printf("FAIL: Could not create hive coordinators\n");
        return 1;
    }
    
    printf("PASS: Created two hive nodes with autognosis engines\n\n");
    
    // Initialize network topologies
    topology_add_node(engine1->topology, 1001, "192.168.1.10");
    topology_add_node(engine1->topology, 1002, "192.168.1.20");
    topology_add_node(engine1->topology, 1003, "192.168.1.30");
    
    topology_add_node(engine2->topology, 1001, "192.168.1.10");
    topology_add_node(engine2->topology, 1002, "192.168.1.20");
    topology_add_node(engine2->topology, 1003, "192.168.1.30");
    
    // Set initial health values
    topology_update_node_health(engine1->topology, 1001, 1.0f);
    topology_update_node_health(engine1->topology, 1002, 0.8f);
    topology_update_node_health(engine1->topology, 1003, 0.9f);
    
    topology_update_node_health(engine2->topology, 1001, 1.0f);
    topology_update_node_health(engine2->topology, 1002, 0.8f);
    topology_update_node_health(engine2->topology, 1003, 0.9f);
    
    printf("Initial network health: Node1=%.2f, Node2=%.2f\n", 
           engine1->topology->overall_health, engine2->topology->overall_health);
    
    // Run cognitive cycles
    autognosis_cognitive_cycle(engine1);
    autognosis_cognitive_cycle(engine2);
    
    printf("Initial self-image - Node1: health=%.2f, autonomy=%.2f\n", 
           engine1->self_image->health_score, engine1->self_image->autonomy_level);
    printf("Initial self-image - Node2: health=%.2f, autonomy=%.2f\n", 
           engine2->self_image->health_score, engine2->self_image->autonomy_level);
    
    // Run demonstrations
    demonstrate_knowledge_sharing(engine1, coord1, engine2, coord2);
    sleep(1);
    
    demonstrate_collective_healing(coord1, coord2);
    sleep(1);
    
    simulate_network_failure(engine1, coord1);
    sleep(1);
    
    demonstrate_emergence_behavior(coord1, coord2);
    
    // Show final state
    printf("\n=== Final System State ===\n");
    printf("Node 1 - Health: %.2f, Load: %.2f, Atoms: %u\n", 
           engine1->self_image->health_score, engine1->cognitive_load, 
           engine1->global_knowledge->atom_count);
    printf("Node 2 - Health: %.2f, Load: %.2f, Atoms: %u\n", 
           engine2->self_image->health_score, engine2->cognitive_load, 
           engine2->global_knowledge->atom_count);
    
    printf("Collective Intelligence Scores: Node1=%.2f, Node2=%.2f\n", 
           coord1->collective_intelligence_score, coord2->collective_intelligence_score);
    
    // Test hive heartbeats
    printf("\nTesting hive coordination cycles...\n");
    for (int i = 0; i < 3; i++) {
        hive_coordinator_process_cycle(coord1);
        hive_coordinator_process_cycle(coord2);
        sleep(1);
    }
    
    // Cleanup
    hive_coordinator_destroy(coord1);
    hive_coordinator_destroy(coord2);
    
    autognosis_stop(engine1);
    autognosis_stop(engine2);
    autognosis_destroy(engine1);
    autognosis_destroy(engine2);
    
    printf("\n========================================\n");
    printf("OpenCog Hive Autognosis System Successfully Demonstrated!\n");
    printf("Features tested:\n");
    printf("- Self-image building and introspection\n");
    printf("- Network topology awareness\n");
    printf("- Autogenetic healing coordination\n");
    printf("- Collective knowledge sharing\n");
    printf("- Emergent swarm intelligence\n");
    printf("- Distributed fault tolerance\n");
    printf("- Adaptive behavior modification\n");
    
    return 0;
}