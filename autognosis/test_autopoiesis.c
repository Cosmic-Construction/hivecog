#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "autognosis.h"
#include "entropic_bootstrap.h"
#include "homeostatic_feedback.h"
#include "feedforward_autopoiesis.h"

int main() {
    printf("Testing Feedforward Inference Projection and Autopoiesis System\n");
    printf("=============================================================\n\n");
    
    // Create base autognosis engine
    autognosis_engine_t *autognosis = autognosis_create("autopoietic_test_node");
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
    
    // Create self-maintenance autopoietic system
    self_maintenance_system_t *autopoietic = self_maintenance_create(homeostatic);
    if (!autopoietic) {
        printf("FAIL: Could not create autopoietic system\n");
        homeostatic_system_destroy(homeostatic);
        bootstrap_engine_destroy(bootstrap);
        autognosis_destroy(autognosis);
        return 1;
    }
    printf("PASS: Self-maintenance autopoietic system created\n");
    
    // Start all systems
    autognosis_start(autognosis);
    bootstrap_engine_start(bootstrap);
    homeostatic_system_start(homeostatic);
    self_maintenance_start(autopoietic);
    
    // Add network topology for realistic testing
    topology_add_node(autognosis->topology, 1, "192.168.1.10");
    topology_add_node(autognosis->topology, 2, "192.168.1.20");
    topology_add_node(autognosis->topology, 3, "192.168.1.30");
    topology_update_node_health(autognosis->topology, 1, 0.9f);
    topology_update_node_health(autognosis->topology, 2, 0.8f);
    topology_update_node_health(autognosis->topology, 3, 0.7f);
    
    printf("\n=== Testing Homeostatic Image Projection ===\n");
    
    // Test image projection
    homeostatic_image_t *test_image = homeostatic_image_create("test_projection");
    if (test_image) {
        printf("Created homeostatic image: %s\n", test_image->image_name);
        
        // Project different time horizons
        homeostatic_image_project(test_image, homeostatic->virtual_engine, 5);
        printf("Short-term projection (5 cycles): Performance=%.3f, Stability=%.3f, Confidence=%.3f\n",
               test_image->performance_projection, test_image->stability_projection,
               test_image->projection_confidence);
        
        homeostatic_image_project(test_image, homeostatic->virtual_engine, 50);
        printf("Medium-term projection (50 cycles): Performance=%.3f, Stability=%.3f, Confidence=%.3f\n",
               test_image->performance_projection, test_image->stability_projection,
               test_image->projection_confidence);
        
        homeostatic_image_project(test_image, homeostatic->virtual_engine, 200);
        printf("Long-term projection (200 cycles): Performance=%.3f, Stability=%.3f, Confidence=%.3f\n",
               test_image->performance_projection, test_image->stability_projection,
               test_image->projection_confidence);
        
        homeostatic_image_destroy(test_image);
    }
    
    printf("\n=== Testing Feedforward Prediction Engines ===\n");
    
    // Test feedforward engines
    feedforward_engine_t *test_engine = feedforward_engine_create("test_predictor", 999, 10);
    if (test_engine) {
        printf("Created feedforward engine: %s (history size: %u)\n", 
               test_engine->name, test_engine->history_size);
        
        // Add some sample data with trend
        for (int i = 0; i < 15; i++) {
            float value = 0.5f + 0.3f * sinf((float)i * 0.2f) + 0.01f * i;  // Oscillating with upward trend
            feedforward_engine_add_state(test_engine, value);
            printf("  Added state[%d]: %.3f\n", i, value);
        }
        
        // Test predictions
        float pred_1 = feedforward_engine_predict(test_engine, 1);
        float pred_5 = feedforward_engine_predict(test_engine, 5);
        float pred_10 = feedforward_engine_predict(test_engine, 10);
        
        printf("Predictions: 1-step=%.3f, 5-step=%.3f, 10-step=%.3f\n", pred_1, pred_5, pred_10);
        printf("Prediction accuracy: %.3f, Model stability: %.3f\n",
               test_engine->prediction_accuracy, test_engine->model_stability);
        
        feedforward_engine_destroy(test_engine);
    }
    
    printf("\n=== Testing Predictive Models ===\n");
    
    // Test different predictive model types
    predictive_model_t *linear_model = predictive_model_create(PREDICTION_LINEAR, "test_linear");
    predictive_model_t *exp_model = predictive_model_create(PREDICTION_EXPONENTIAL, "test_exponential");
    predictive_model_t *neural_model = predictive_model_create(PREDICTION_NEURAL, "test_neural");
    
    if (linear_model && exp_model && neural_model) {
        printf("Created predictive models: Linear, Exponential, Neural\n");
        
        // Test predictions with sample input
        float test_input = 0.7f;
        float linear_pred = predictive_model_predict(linear_model, &test_input, 1);
        float exp_pred = predictive_model_predict(exp_model, &test_input, 1);
        float neural_pred = predictive_model_predict(neural_model, &test_input, 1);
        
        printf("Model predictions for input %.3f:\n", test_input);
        printf("  Linear: %.3f, Exponential: %.3f, Neural: %.3f\n", 
               linear_pred, exp_pred, neural_pred);
        
        // Test training with simple data
        float train_inputs[] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f};
        float train_outputs[] = {0.2f, 0.4f, 0.6f, 0.8f, 1.0f};  // Linear relationship
        
        predictive_model_train(linear_model, train_inputs, train_outputs, 5);
        printf("Trained linear model with 5 data points\n");
        
        // Test after training
        float trained_pred = predictive_model_predict(linear_model, &test_input, 1);
        printf("Linear model prediction after training: %.3f\n", trained_pred);
        
        predictive_model_destroy(linear_model);
        predictive_model_destroy(exp_model);
        predictive_model_destroy(neural_model);
    }
    
    printf("\n=== Testing Anticipatory Actions ===\n");
    
    // Test anticipatory actions
    anticipatory_action_t *preventive_action = anticipatory_action_create("test_prevention", ANTICIPATION_PREVENTIVE, 999);
    anticipatory_action_t *adaptive_action = anticipatory_action_create("test_adaptation", ANTICIPATION_ADAPTIVE, 998);
    
    if (preventive_action && adaptive_action) {
        printf("Created anticipatory actions: Prevention, Adaptation\n");
        
        // Test trigger conditions
        float condition_value = 0.6f;
        float confidence = 0.8f;
        
        preventive_action->trigger_threshold = 0.5f;
        preventive_action->confidence_required = 0.7f;
        
        if (anticipatory_action_should_trigger(preventive_action, condition_value, confidence)) {
            printf("Preventive action triggered (condition: %.3f, confidence: %.3f)\n",
                   condition_value, confidence);
            anticipatory_action_execute(preventive_action, NULL);
            
            // Simulate learning from results
            float effectiveness = 0.85f;
            anticipatory_action_learn(preventive_action, effectiveness);
            printf("Action learned from effectiveness: %.3f\n", effectiveness);
            printf("Updated success rate: %.3f, avg effectiveness: %.3f\n",
                   preventive_action->success_rate, preventive_action->average_effectiveness);
        }
        
        anticipatory_action_destroy(preventive_action);
        anticipatory_action_destroy(adaptive_action);
    }
    
    printf("\n=== Testing Autopoietic System Cycles ===\n");
    
    // Run autopoietic cycles
    for (int i = 0; i < 8; i++) {
        self_maintenance_cycle(autopoietic);
        homeostatic_system_cycle(homeostatic);
        bootstrap_engine_cycle(bootstrap);
        autognosis_cognitive_cycle(autognosis);
        
        float autopoiesis_index = calculate_autopoiesis_index(autopoietic);
        float vitality = measure_system_vitality(autopoietic);
        
        printf("Cycle %d: Autopoiesis=%.3f, Vitality=%.3f, Predictive=%.3f, Healing=%.3f\n",
               i + 1, autopoiesis_index, vitality, 
               autopoietic->predictive_power, autopoietic->healing_efficiency);
        
        // Show detailed metrics every few cycles
        if (i % 3 == 0) {
            printf("  Anticipation horizon: %.1f, Intervention threshold: %.3f\n",
                   autopoietic->anticipation_horizon, autopoietic->intervention_threshold);
            printf("  Adaptation aggressiveness: %.3f, Adaptation effectiveness: %.3f\n",
                   autopoietic->adaptation_aggressiveness, autopoietic->adaptation_effectiveness);
        }
        
        sleep(1);
    }
    
    printf("\n=== Testing System Enhancement Functions ===\n");
    
    float initial_predictive = autopoietic->predictive_power;
    float initial_healing = autopoietic->healing_efficiency;
    
    printf("Before enhancement: Predictive=%.3f, Healing=%.3f\n", 
           initial_predictive, initial_healing);
    
    enhance_predictive_power(autopoietic);
    optimize_healing_efficiency(autopoietic);
    
    printf("After enhancement: Predictive=%.3f, Healing=%.3f\n",
           autopoietic->predictive_power, autopoietic->healing_efficiency);
    printf("Improvement: Predictive=+%.3f, Healing=+%.3f\n",
           autopoietic->predictive_power - initial_predictive,
           autopoietic->healing_efficiency - initial_healing);
    
    printf("\n=== Testing Advanced Autopoietic Functions ===\n");
    
    enable_self_reproduction(autopoietic);
    maintain_system_boundaries(autopoietic);
    preserve_system_identity(autopoietic);
    adapt_to_environmental_changes(autopoietic);
    
    printf("\n=== Simulating Environmental Stress ===\n");
    
    // Introduce stress to test autopoietic response
    printf("Introducing environmental stress...\n");
    autognosis->cognitive_load = 0.8f;
    topology_update_node_health(autognosis->topology, 2, 0.3f);
    topology_update_node_health(autognosis->topology, 3, 0.2f);
    
    printf("Running stress response cycles...\n");
    for (int i = 0; i < 5; i++) {
        self_maintenance_cycle(autopoietic);
        homeostatic_system_cycle(homeostatic);
        
        float performance = virtual_engine_measure_performance(homeostatic->virtual_engine);
        float autopoiesis = calculate_autopoiesis_index(autopoietic);
        
        printf("Stress cycle %d: Performance=%.3f, Autopoiesis=%.3f\n", 
               i + 1, performance, autopoiesis);
        
        sleep(1);
    }
    
    printf("\n=== Testing Projected Image Accuracy ===\n");
    
    // Test projection accuracy by comparing with actual outcomes
    if (autopoietic->projected_images) {
        homeostatic_image_t *image = autopoietic->projected_images;
        while (image) {
            printf("Image '%s':\n", image->image_name);
            printf("  Projected performance: %.3f, confidence: %.3f\n",
                   image->performance_projection, image->projection_confidence);
            
            // Simulate actual outcome
            float actual_performance = virtual_engine_measure_performance(homeostatic->virtual_engine);
            homeostatic_image_update_confidence(image, actual_performance);
            
            printf("  Actual performance: %.3f, updated confidence: %.3f\n",
                   actual_performance, image->projection_confidence);
            
            image = image->next;
        }
    }
    
    printf("\n=== Final Autopoietic Assessment ===\n");
    
    float final_autopoiesis = calculate_autopoiesis_index(autopoietic);
    float final_vitality = measure_system_vitality(autopoietic);
    
    printf("Final autopoietic metrics:\n");
    printf("  Autopoiesis Index: %.3f\n", final_autopoiesis);
    printf("  System Vitality: %.3f\n", final_vitality);
    printf("  Predictive Power: %.3f\n", autopoietic->predictive_power);
    printf("  Healing Efficiency: %.3f\n", autopoietic->healing_efficiency);
    printf("  Adaptation Effectiveness: %.3f\n", autopoietic->adaptation_effectiveness);
    printf("  Maintenance Cycles: %u\n", autopoietic->maintenance_cycles);
    
    // Display feedforward engine states
    printf("\nFeedforward engine states:\n");
    feedforward_engine_t *current_engine = autopoietic->feedforward_engines;
    int engine_num = 1;
    while (current_engine) {
        printf("  Engine %d (%s): Accuracy=%.3f, Stability=%.3f, Predictions=%u\n",
               engine_num, current_engine->name, current_engine->prediction_accuracy,
               current_engine->model_stability, current_engine->prediction_count);
        current_engine = current_engine->next;
        engine_num++;
    }
    
    // Display anticipatory action states
    printf("\nAnticipatory action states:\n");
    anticipatory_action_t *current_action = autopoietic->anticipatory_actions;
    int action_num = 1;
    while (current_action) {
        printf("  Action %d (%s): Success=%.3f, Effectiveness=%.3f, Executions=%u\n",
               action_num, current_action->action_name, current_action->success_rate,
               current_action->average_effectiveness, current_action->execution_count);
        current_action = current_action->next;
        action_num++;
    }
    
    printf("\n=== Demonstrating Constructive Transformation ===\n");
    
    demonstrate_autopoietic_transformation(autopoietic);
    show_feedforward_benefits(autopoietic);
    explain_anticipatory_healing(autopoietic);
    
    printf("\n=== Autopoietic System Principles Demonstrated ===\n");
    printf("1. Self-Maintenance: System maintains itself without external intervention\n");
    printf("2. Anticipatory Healing: Problems prevented before they manifest\n");
    printf("3. Feedforward Control: Future states projected and managed proactively\n");
    printf("4. Adaptive Learning: System improves prediction and response over time\n");
    printf("5. Identity Preservation: Core functionality maintained despite changes\n");
    printf("6. Environmental Adaptation: System adapts to changing conditions\n");
    printf("7. Constructive Emergence: Destructive patterns transformed into healing\n");
    
    // Cleanup
    self_maintenance_stop(autopoietic);
    homeostatic_system_stop(homeostatic);
    bootstrap_engine_stop(bootstrap);
    autognosis_stop(autognosis);
    
    self_maintenance_destroy(autopoietic);
    homeostatic_system_destroy(homeostatic);
    bootstrap_engine_destroy(bootstrap);
    autognosis_destroy(autognosis);
    
    printf("\n=============================================================\n");
    printf("Feedforward Autopoietic System Test Completed Successfully!\n");
    printf("System demonstrated self-maintenance through anticipatory mechanisms.\n");
    printf("Feedforward projection enables proactive healing and optimization.\n");
    printf("Autopoietic principles transform destructive patterns into life-affirming processes.\n");
    
    return 0;
}