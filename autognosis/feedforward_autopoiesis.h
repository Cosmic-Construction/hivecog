#ifndef __FEEDFORWARD_AUTOPOIESIS_H
#define __FEEDFORWARD_AUTOPOIESIS_H

#include "autognosis.h"
#include "entropic_bootstrap.h"
#include "homeostatic_feedback.h"
#include <stdint.h>
#include <time.h>

// Homeostatic image projection system
typedef struct homeostatic_image {
    char image_name[64];
    float stability_projection;      // Projected system stability
    float health_projection;         // Projected system health
    float performance_projection;    // Projected performance metric
    float resilience_projection;     // Projected resilience factor
    float entropy_projection;        // Projected entropy level
    
    // Temporal projections
    float short_term_projection;     // 1-10 cycles ahead
    float medium_term_projection;    // 10-100 cycles ahead
    float long_term_projection;      // 100+ cycles ahead
    
    // Confidence intervals
    float projection_confidence;     // Confidence in projections
    float uncertainty_bound;         // Uncertainty bound estimate
    
    time_t projection_time;
    time_t validity_period;          // How long projection is valid
    
    struct homeostatic_image *next;
} homeostatic_image_t;

// Feedforward inference engine for autopoiesis
typedef struct feedforward_engine {
    uint32_t engine_id;
    char name[64];
    
    // Predictive models
    float *state_history;            // Circular buffer of past states
    uint32_t history_size;
    uint32_t history_index;
    
    // Model parameters
    float prediction_horizon;        // How far ahead to predict
    float learning_rate;             // Model adaptation rate
    float momentum;                  // Prediction momentum
    float volatility;                // Model uncertainty measure
    
    // Autopoietic functions
    void (*predict_future_state)(struct feedforward_engine *, float current_state, float *prediction);
    void (*generate_maintenance_plan)(struct feedforward_engine *, homeostatic_image_t *image);
    void (*anticipate_disturbances)(struct feedforward_engine *, float *disturbance_probability);
    void (*update_model)(struct feedforward_engine *, float actual_state, float predicted_state);
    
    // Performance metrics
    float prediction_accuracy;       // Historical accuracy
    float model_stability;           // Model parameter stability
    uint32_t prediction_count;       // Number of predictions made
    uint32_t accurate_predictions;   // Number of accurate predictions
    
    time_t last_prediction;
    struct feedforward_engine *next;
} feedforward_engine_t;

// Predictive models for different system aspects
typedef enum {
    PREDICTION_LINEAR,               // Linear extrapolation
    PREDICTION_EXPONENTIAL,          // Exponential growth/decay
    PREDICTION_OSCILLATORY,          // Periodic/cyclical patterns
    PREDICTION_CHAOTIC,              // Chaotic/strange attractor
    PREDICTION_NEURAL,               // Neural network-based
    PREDICTION_ENSEMBLE              // Ensemble of multiple models
} prediction_model_type_t;

typedef struct predictive_model {
    prediction_model_type_t type;
    char target_parameter[64];
    
    // Model coefficients
    float *coefficients;
    uint32_t coefficient_count;
    
    // Model state
    float bias;
    float variance;
    float correlation;
    float r_squared;                 // Coefficient of determination
    
    // Training data
    float *training_inputs;
    float *training_outputs;
    uint32_t training_size;
    
    // Model functions
    float (*predict)(struct predictive_model *, float *inputs, uint32_t input_count);
    void (*train)(struct predictive_model *, float *inputs, float *outputs, uint32_t data_size);
    void (*validate)(struct predictive_model *, float *test_inputs, float *test_outputs, uint32_t test_size);
    
    time_t last_training;
    struct predictive_model *next;
} predictive_model_t;

// Anticipatory healing and adaptation
typedef enum {
    ANTICIPATION_PREVENTIVE,         // Prevent problems before they occur
    ANTICIPATION_PREEMPTIVE,         // Take action before threshold reached
    ANTICIPATION_ADAPTIVE,           // Adapt system proactively
    ANTICIPATION_TRANSFORMATIVE,     // Transform system structure
    ANTICIPATION_EMERGENT            // Enable emergent solutions
} anticipation_type_t;

typedef struct anticipatory_action {
    uint32_t action_id;
    char action_name[64];
    anticipation_type_t type;
    
    // Trigger conditions
    char trigger_condition[128];
    float trigger_threshold;
    float confidence_required;
    
    // Action parameters
    float action_strength;           // Intensity of action
    float action_duration;           // How long action lasts
    float action_cost;               // Resource cost of action
    float expected_benefit;          // Expected positive outcome
    
    // Execution functions
    void (*prepare_action)(struct anticipatory_action *);
    void (*execute_action)(struct anticipatory_action *, void *context);
    void (*monitor_results)(struct anticipatory_action *, float *effectiveness);
    
    // Learning and adaptation
    uint32_t execution_count;
    float success_rate;
    float average_effectiveness;
    
    time_t last_execution;
    struct anticipatory_action *next;
} anticipatory_action_t;

// Self-maintenance system for autopoiesis
typedef struct self_maintenance_system {
    homeostatic_system_t *homeostatic;
    feedforward_engine_t *feedforward_engines;
    predictive_model_t *predictive_models;
    anticipatory_action_t *anticipatory_actions;
    homeostatic_image_t *projected_images;
    
    // System parameters
    float autopoiesis_index;         // Measure of self-maintenance capability
    float anticipation_horizon;      // How far ahead system looks
    float intervention_threshold;     // When to take anticipatory action
    float adaptation_aggressiveness; // How aggressively to adapt
    
    // Core functions
    void (*project_homeostatic_images)(struct self_maintenance_system *);
    void (*predict_system_evolution)(struct self_maintenance_system *);
    void (*plan_maintenance_actions)(struct self_maintenance_system *);
    void (*execute_anticipatory_healing)(struct self_maintenance_system *);
    void (*update_predictive_models)(struct self_maintenance_system *);
    void (*assess_autopoietic_health)(struct self_maintenance_system *);
    
    // State tracking
    float system_vitality;           // Overall system life/energy
    float adaptation_effectiveness;   // How well system adapts
    float predictive_power;          // Quality of predictions
    float healing_efficiency;        // Efficiency of healing actions
    
    int running;
    time_t last_cycle;
    uint32_t maintenance_cycles;
    
} self_maintenance_system_t;

// Core functions
self_maintenance_system_t* self_maintenance_create(homeostatic_system_t *homeostatic);
void self_maintenance_destroy(self_maintenance_system_t *system);
void self_maintenance_start(self_maintenance_system_t *system);
void self_maintenance_stop(self_maintenance_system_t *system);
void self_maintenance_cycle(self_maintenance_system_t *system);

// Homeostatic image functions
homeostatic_image_t* homeostatic_image_create(const char *name);
void homeostatic_image_destroy(homeostatic_image_t *image);
void homeostatic_image_project(homeostatic_image_t *image, virtual_engine_state_t *current_state, 
                              uint32_t cycles_ahead);
void homeostatic_image_update_confidence(homeostatic_image_t *image, float actual_outcome);

// Feedforward engine functions
feedforward_engine_t* feedforward_engine_create(const char *name, uint32_t id, uint32_t history_size);
void feedforward_engine_destroy(feedforward_engine_t *engine);
void feedforward_engine_add_state(feedforward_engine_t *engine, float state_value);
float feedforward_engine_predict(feedforward_engine_t *engine, uint32_t steps_ahead);
void feedforward_engine_train(feedforward_engine_t *engine);

// Predictive model functions
predictive_model_t* predictive_model_create(prediction_model_type_t type, const char *target);
void predictive_model_destroy(predictive_model_t *model);
float predictive_model_predict(predictive_model_t *model, float *inputs, uint32_t input_count);
void predictive_model_train(predictive_model_t *model, float *inputs, float *outputs, uint32_t data_size);
void predictive_model_validate(predictive_model_t *model, float *test_inputs, float *test_outputs, uint32_t test_size);

// Anticipatory action functions
anticipatory_action_t* anticipatory_action_create(const char *name, anticipation_type_t type, uint32_t id);
void anticipatory_action_destroy(anticipatory_action_t *action);
int anticipatory_action_should_trigger(anticipatory_action_t *action, float condition_value, float confidence);
void anticipatory_action_execute(anticipatory_action_t *action, void *context);
void anticipatory_action_learn(anticipatory_action_t *action, float effectiveness);

// System health and autopoiesis functions
float calculate_autopoiesis_index(self_maintenance_system_t *system);
float measure_system_vitality(self_maintenance_system_t *system);
void enhance_predictive_power(self_maintenance_system_t *system);
void optimize_healing_efficiency(self_maintenance_system_t *system);

// Advanced autopoietic functions
void enable_self_reproduction(self_maintenance_system_t *system);
void maintain_system_boundaries(self_maintenance_system_t *system);
void preserve_system_identity(self_maintenance_system_t *system);
void adapt_to_environmental_changes(self_maintenance_system_t *system);

// Constructive transformation for autopoiesis
void demonstrate_autopoietic_transformation(self_maintenance_system_t *system);
void show_feedforward_benefits(self_maintenance_system_t *system);
void explain_anticipatory_healing(self_maintenance_system_t *system);

#endif /* __FEEDFORWARD_AUTOPOIESIS_H */