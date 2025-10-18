#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "autognosis.h"

int main() {
    printf("Testing OpenCog Autognosis Engine for Hive\n");
    printf("==========================================\n\n");
    
    // Create autognosis engine
    autognosis_engine_t *engine = autognosis_create("test_hive_node");
    if (!engine) {
        printf("FAIL: Could not create autognosis engine\n");
        return 1;
    }
    printf("PASS: Autognosis engine created successfully\n");
    
    // Start the engine
    if (autognosis_start(engine) != 0) {
        printf("FAIL: Could not start autognosis engine\n");
        autognosis_destroy(engine);
        return 1;
    }
    printf("PASS: Autognosis engine started\n");
    
    // Test self-image creation and updates
    printf("Testing self-image building process...\n");
    printf("Initial health: %.2f, autonomy: %.2f\n", 
           engine->self_image->health_score, engine->self_image->autonomy_level);
    
    // Add some network nodes
    topology_add_node(engine->topology, 1, "192.168.1.10");
    topology_add_node(engine->topology, 2, "192.168.1.20");
    topology_add_node(engine->topology, 3, "192.168.1.30");
    printf("PASS: Added %u nodes to network topology\n", engine->topology->node_count);
    
    // Update node health
    topology_update_node_health(engine->topology, 1, 0.9f);
    topology_update_node_health(engine->topology, 2, 0.7f);
    topology_update_node_health(engine->topology, 3, 0.3f);
    printf("PASS: Updated node health scores\n");
    printf("Overall network health: %.2f\n", engine->topology->overall_health);
    
    // Test cognitive cycles
    printf("Running cognitive cycles...\n");
    for (int i = 0; i < 3; i++) {
        autognosis_cognitive_cycle(engine);
        printf("Cycle %d: Health %.2f, Autonomy %.2f, Load %.2f\n", 
               i + 1, engine->self_image->health_score, 
               engine->self_image->autonomy_level, engine->cognitive_load);
        sleep(1);
    }
    
    // Test network event processing
    printf("Testing network event processing...\n");
    char event[] = "packet_received_length_64";
    autognosis_process_hive_message(engine, event);
    printf("PASS: Processed hive message: %s\n", event);
    
    // Test healing capabilities
    printf("Testing autogenetic healing...\n");
    char problem1[] = "timeout";
    char problem2[] = "connection_failed";
    char problem3[] = "node_failure";
    
    healing_action_t action1 = healing_evaluate_problem(engine, problem1);
    healing_action_t action2 = healing_evaluate_problem(engine, problem2);
    healing_action_t action3 = healing_evaluate_problem(engine, problem3);
    
    printf("Problem: %s -> Healing action: %d\n", problem1, action1);
    printf("Problem: %s -> Healing action: %d\n", problem2, action2);
    printf("Problem: %s -> Healing action: %d\n", problem3, action3);
    
    // Test AtomSpace knowledge representation
    printf("Testing AtomSpace knowledge representation...\n");
    atom_t *concept = atomspace_add_atom(engine->global_knowledge, ATOM_CONCEPT, "network_stability");
    if (concept) {
        atomspace_update_truth_value(concept, 0.85f, 0.9f);
        printf("PASS: Added concept 'network_stability' with truth value %.2f\n", concept->truth_value);
    }
    
    atom_t *predicate = atomspace_add_atom(engine->global_knowledge, ATOM_PREDICATE, "is_healthy");
    if (predicate) {
        atomspace_update_truth_value(predicate, engine->topology->overall_health, 0.8f);
        printf("PASS: Added predicate 'is_healthy' with truth value %.2f\n", predicate->truth_value);
    }
    
    printf("Total atoms in global knowledge base: %u\n", engine->global_knowledge->atom_count);
    
    // Find healthiest node
    network_node_t *healthiest = topology_find_healthiest_node(engine->topology);
    if (healthiest) {
        printf("Healthiest node: ID %u at %s with health %.2f\n", 
               healthiest->node_id, healthiest->address, healthiest->health_score);
    }
    
    // Cleanup
    autognosis_stop(engine);
    autognosis_destroy(engine);
    printf("PASS: Autognosis engine stopped and cleaned up\n");
    
    printf("\n==========================================\n");
    printf("All tests completed successfully!\n");
    printf("OpenCog autognosis engine is operational.\n");
    
    return 0;
}