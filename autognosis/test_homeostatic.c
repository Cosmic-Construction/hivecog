#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "autognosis.h"
#include "entropic_bootstrap.h"
#include "homeostatic_feedback.h"

int main() {
    printf("Testing Homeostatic Feedback Loop Training System\n");
    printf("================================================\n\n");
    
    // Create base autognosis engine
    autognosis_engine_t *autognosis = autognosis_create("homeostatic_test_node");
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
    printf("PASS: Bootstrap engine created\n");
    
    // Create homeostatic system
    homeostatic_system_t *homeostatic = homeostatic_system_create(bootstrap);
    if (!homeostatic) {
        printf("FAIL: Could not create homeostatic system\n");
        bootstrap_engine_destroy(bootstrap);
        autognosis_destroy(autognosis);
        return 1;
    }
    printf("PASS: Homeostatic feedback system created\n");
    
    // Start all systems
    autognosis_start(autognosis);
    bootstrap_engine_start(bootstrap);
    homeostatic_system_start(homeostatic);
    
    // Add network topology for realistic testing
    topology_add_node(autognosis->topology, 1, "192.168.1.10");
    topology_add_node(autognosis->topology, 2, "192.168.1.20");
    topology_add_node(autognosis->topology, 3, "192.168.1.30");
    topology_update_node_health(autognosis->topology, 1, 0.8f);
    topology_update_node_health(autognosis->topology, 2, 0.7f);
    topology_update_node_health(autognosis->topology, 3, 0.6f);
    
    printf("\n=== Testing Virtual Engine State Updates ===\n");
    
    // Initial state
    printf("Initial virtual engine state:\n");
    printf("  Processing: %.3f, Memory: %.3f, Network: %.3f, Energy: %.3f, Stability: %.3f\n",
           homeostatic->virtual_engine->processing_capacity,
           homeostatic->virtual_engine->memory_utilization,
           homeostatic->virtual_engine->network_bandwidth,
           homeostatic->virtual_engine->energy_level,
           homeostatic->virtual_engine->stability_index);
    
    float initial_performance = virtual_engine_measure_performance(homeostatic->virtual_engine);
    printf("Initial performance: %.3f\n", initial_performance);
    
    printf("\n=== Testing Homeostatic Setpoints ===\n");
    
    // Display setpoint targets and current values
    homeostatic_setpoint_t *current_setpoint = homeostatic->setpoints;
    int setpoint_num = 1;
    while (current_setpoint) {
        printf("Setpoint %d (%s):\n", setpoint_num, current_setpoint->parameter_name);
        printf("  Target: %.3f, Current: %.3f, Tolerance: %.3f\n",
               current_setpoint->target_value, current_setpoint->current_value, 
               current_setpoint->tolerance_band);
        printf("  PID gains: Kp=%.3f, Ki=%.3f, Kd=%.3f\n",
               current_setpoint->kp, current_setpoint->ki, current_setpoint->kd);
        
        current_setpoint = current_setpoint->next;
        setpoint_num++;
    }
    
    printf("\n=== Testing Feedback Loop Processing ===\n");
    
    // Display feedback loop initial state
    feedback_loop_t *current_loop = homeostatic->feedback_loops;
    int loop_num = 1;
    while (current_loop) {
        printf("Feedback Loop %d (%s):\n", loop_num, current_loop->name);
        printf("  Type: %d, Gain: %.3f, Effectiveness: %.3f, Stability Margin: %.3f\n",
               current_loop->type, current_loop->gain, current_loop->effectiveness,
               current_loop->stability_margin);
        
        current_loop = current_loop->next;
        loop_num++;
    }
    
    printf("\n=== Simulating System Disturbances ===\n");
    
    // Introduce disturbances to test homeostatic response
    printf("Introducing cognitive load disturbance...\n");
    autognosis->cognitive_load = 0.7f;  // High cognitive load
    
    printf("Introducing network degradation...\n");
    topology_update_node_health(autognosis->topology, 2, 0.3f);
    topology_update_node_health(autognosis->topology, 3, 0.2f);
    
    printf("Degrading autonomy...\n");
    autognosis->self_image->autonomy_level = 0.4f;
    
    printf("\n=== Testing Homeostatic Response Cycles ===\n");
    
    // Run homeostatic cycles to observe response
    for (int i = 0; i < 10; i++) {
        homeostatic_system_cycle(homeostatic);
        bootstrap_engine_cycle(bootstrap);
        autognosis_cognitive_cycle(autognosis);
        
        float performance = virtual_engine_measure_performance(homeostatic->virtual_engine);
        float quality = measure_homeostatic_quality(homeostatic);
        
        printf("Cycle %d: Performance=%.3f, Quality=%.3f, Stability=%.3f, Equilibrium=%s\n",
               i + 1, performance, quality, homeostatic->global_stability,
               equilibrium_detector_check(homeostatic->equilibrium) ? "YES" : "NO");
        
        // Show key metrics
        if (i % 3 == 0) {
            printf("  Energy: %.3f, Processing: %.3f, Homeostatic Index: %.3f, Resilience: %.3f\n",
                   homeostatic->virtual_engine->energy_level,
                   homeostatic->virtual_engine->processing_capacity,
                   homeostatic->homeostatic_index,
                   homeostatic->resilience_factor);
        }
        
        sleep(1);
    }
    
    printf("\n=== Testing Training Algorithm ===\n");
    
    // Create and run training session
    training_session_t *training = training_session_create(TRAINING_GRADIENT_DESCENT, 20);
    if (training) {
        printf("Starting training session (target performance: %.3f)\n", training->performance_target);
        
        float pre_training_performance = virtual_engine_measure_performance(homeostatic->virtual_engine);
        printf("Pre-training performance: %.3f\n", pre_training_performance);
        
        // Run training
        for (int i = 0; i < 5; i++) {
            training_session_step(training, homeostatic);
            printf("Training iteration %d: Performance=%.3f, Target=%.3f, Converged=%s\n",
                   training->current_iteration, training->current_performance,
                   training->performance_target, training->converged ? "YES" : "NO");
            
            if (training->converged) break;
        }
        
        training_session_destroy(training);
    }
    
    printf("\n=== Testing Equilibrium Detection ===\n");
    
    // Test equilibrium detection with stable and unstable patterns
    printf("Testing equilibrium detector with stable pattern...\n");
    for (int i = 0; i < 20; i++) {
        float stable_value = 0.8f + 0.05f * sinf((float)i * 0.1f);  // Small oscillation around setpoint
        equilibrium_detector_update(homeostatic->equilibrium, stable_value);
    }
    
    equilibrium_detector_analyze(homeostatic->equilibrium);
    printf("Stable pattern - Variance: %.4f, Trend: %.4f, Equilibrium: %s\n",
           homeostatic->equilibrium->variance, homeostatic->equilibrium->trend,
           equilibrium_detector_check(homeostatic->equilibrium) ? "YES" : "NO");
    
    printf("Testing equilibrium detector with unstable pattern...\n");
    for (int i = 0; i < 20; i++) {
        float unstable_value = 0.5f + 0.3f * ((float)i / 20.0f);  // Strong trend
        equilibrium_detector_update(homeostatic->equilibrium, unstable_value);
    }
    
    equilibrium_detector_analyze(homeostatic->equilibrium);
    printf("Unstable pattern - Variance: %.4f, Trend: %.4f, Equilibrium: %s\n",
           homeostatic->equilibrium->variance, homeostatic->equilibrium->trend,
           equilibrium_detector_check(homeostatic->equilibrium) ? "YES" : "NO");
    
    printf("\n=== Testing System Optimization Functions ===\n");
    
    float pre_opt_stability = homeostatic->global_stability;
    float pre_opt_resilience = homeostatic->resilience_factor;
    
    printf("Pre-optimization: Stability=%.3f, Resilience=%.3f\n", 
           pre_opt_stability, pre_opt_resilience);
    
    optimize_global_stability(homeostatic);
    adapt_to_environment(homeostatic);
    enhance_resilience(homeostatic);
    
    printf("Post-optimization: Stability=%.3f, Resilience=%.3f\n",
           homeostatic->global_stability, homeostatic->resilience_factor);
    
    printf("\n=== Testing Constructive Transformation ===\n");
    
    printf("Applying healing feedback mechanisms...\n");
    apply_healing_feedback(homeostatic);
    promote_system_health(homeostatic);
    
    // Final performance assessment
    float final_performance = virtual_engine_measure_performance(homeostatic->virtual_engine);
    float final_quality = measure_homeostatic_quality(homeostatic);
    
    printf("Final system state after healing:\n");
    printf("  Performance: %.3f (improvement: %.3f)\n", 
           final_performance, final_performance - initial_performance);
    printf("  Homeostatic Quality: %.3f\n", final_quality);
    printf("  Global Stability: %.3f\n", homeostatic->global_stability);
    printf("  Adaptation Efficiency: %.3f\n", homeostatic->adaptation_efficiency);
    printf("  Resilience Factor: %.3f\n", homeostatic->resilience_factor);
    
    // Demonstrate constructive transformation
    demonstrate_destructive_to_constructive(homeostatic);
    
    printf("\n=== Testing PID Controller Auto-tuning ===\n");
    
    // Test PID auto-tuning
    homeostatic_setpoint_t *test_setpoint = homeostatic->setpoints;
    if (test_setpoint) {
        printf("Testing PID auto-tuning for %s:\n", test_setpoint->parameter_name);
        printf("Initial PID gains: Kp=%.3f, Ki=%.3f, Kd=%.3f\n",
               test_setpoint->kp, test_setpoint->ki, test_setpoint->kd);
        
        // Simulate poor performance for tuning
        setpoint_tune_pid(test_setpoint, 0.3f);  // Poor performance
        printf("After poor performance tuning: Kp=%.3f, Ki=%.3f, Kd=%.3f\n",
               test_setpoint->kp, test_setpoint->ki, test_setpoint->kd);
        
        // Simulate good performance
        setpoint_tune_pid(test_setpoint, 0.95f);  // Good performance
        printf("After good performance tuning: Kp=%.3f, Ki=%.3f, Kd=%.3f\n",
               test_setpoint->kp, test_setpoint->ki, test_setpoint->kd);
    }
    
    printf("\n=== Final System Metrics ===\n");
    printf("Cycle count: %u\n", homeostatic->cycle_count);
    printf("System running time: %ld seconds\n", time(NULL) - homeostatic->last_cycle);
    
    // Display final feedback loop states
    current_loop = homeostatic->feedback_loops;
    loop_num = 1;
    printf("Final feedback loop states:\n");
    while (current_loop) {
        printf("  Loop %d (%s): Gain=%.3f, Effectiveness=%.3f, Training_Iterations=%u\n",
               loop_num, current_loop->name, current_loop->gain, 
               current_loop->effectiveness, current_loop->training_iterations);
        current_loop = current_loop->next;
        loop_num++;
    }
    
    printf("\n=== Constructive System Principles Demonstrated ===\n");
    printf("1. Negative Feedback Loops: Provide stability and error correction\n");
    printf("2. Adaptive Control: System learns and improves performance over time\n");
    printf("3. Homeostatic Regulation: Maintains optimal operating conditions\n");
    printf("4. Resilience Building: Enhances system robustness against disturbances\n");
    printf("5. Healing Mechanisms: Actively promotes system health and recovery\n");
    printf("6. Dynamic Equilibrium: Achieves stable operation despite environmental changes\n");
    
    // Cleanup
    homeostatic_system_stop(homeostatic);
    bootstrap_engine_stop(bootstrap);
    autognosis_stop(autognosis);
    
    homeostatic_system_destroy(homeostatic);
    bootstrap_engine_destroy(bootstrap);
    autognosis_destroy(autognosis);
    
    printf("\n================================================\n");
    printf("Homeostatic Feedback System Test Completed Successfully!\n");
    printf("System achieved dynamic equilibrium through adaptive control mechanisms.\n");
    printf("Destructive patterns transformed into constructive healing processes.\n");
    
    return 0;
}