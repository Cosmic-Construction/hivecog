/*
 * Planetary Transformer Bridge for Autognosis Engine
 * 
 * Integrates the planetary transformer network with the existing
 * OpenCog Hive Autognosis Engine for distributed consciousness.
 */

#ifndef PLANETARY_TRANSFORMER_BRIDGE_H
#define PLANETARY_TRANSFORMER_BRIDGE_H

#include <stdint.h>
#include <stdbool.h>
#include "autognosis.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
typedef struct planetary_transformer planetary_transformer_t;
typedef struct city_attention_head city_attention_head_t;

/* Knowledge encoding for planetary network */
typedef struct transformer_knowledge {
    char city_id[64];
    char specialization[128];
    float *knowledge_vector;
    uint32_t vector_dimension;
    float reputation;
    float budget;
    uint64_t timestamp;
} transformer_knowledge_t;

/* Attention query from city */
typedef struct transformer_query {
    char source_city[64];
    char problem_type[128];
    float urgency;
    float *query_vector;
    uint32_t vector_dimension;
    float max_cost;
} transformer_query_t;

/* Attention response from network */
typedef struct transformer_response {
    char *contributing_cities[32];
    uint32_t num_contributors;
    float *solution_vector;
    uint32_t vector_dimension;
    float total_cost;
    float confidence;
} transformer_response_t;

/* Economic transaction record */
typedef struct economic_transaction {
    char from_city[64];
    char to_city[64];
    float amount;
    float value_created;
    uint64_t timestamp;
    bool success;
} economic_transaction_t;

/*
 * Initialize planetary transformer integration
 * 
 * Connects autognosis engine to the planetary transformer network
 * 
 * @param engine Autognosis engine instance
 * @param city_id Unique identifier for this city/node
 * @param specialization City's area of expertise
 * @return Planetary transformer instance or NULL on error
 */
planetary_transformer_t *planetary_transformer_init(
    autognosis_engine_t *engine,
    const char *city_id,
    const char *specialization
);

/*
 * Publish knowledge to planetary network
 * 
 * Shares local autognosis knowledge with the global transformer network
 * 
 * @param transformer Planetary transformer instance
 * @param knowledge Knowledge to share
 * @return 0 on success, -1 on error
 */
int planetary_transformer_publish(
    planetary_transformer_t *transformer,
    const transformer_knowledge_t *knowledge
);

/*
 * Query planetary network for knowledge
 * 
 * Performs cross-attention to other cities to gather solutions
 * 
 * @param transformer Planetary transformer instance
 * @param query Query describing the problem
 * @param response Output response from network
 * @return 0 on success, -1 on error
 */
int planetary_transformer_query(
    planetary_transformer_t *transformer,
    const transformer_query_t *query,
    transformer_response_t *response
);

/*
 * Encode autognosis state as knowledge vector
 * 
 * Converts autognosis engine state into a vector representation
 * suitable for the planetary transformer network
 * 
 * @param engine Autognosis engine instance
 * @param vector_out Output vector (must be pre-allocated)
 * @param dimension Dimension of output vector
 * @return 0 on success, -1 on error
 */
int encode_autognosis_state(
    autognosis_engine_t *engine,
    float *vector_out,
    uint32_t dimension
);

/*
 * Decode transformer response into autognosis actions
 * 
 * Translates planetary transformer solutions into autognosis
 * healing actions and knowledge updates
 * 
 * @param engine Autognosis engine instance
 * @param response Transformer network response
 * @return 0 on success, -1 on error
 */
int decode_transformer_response(
    autognosis_engine_t *engine,
    const transformer_response_t *response
);

/*
 * Report economic transaction
 * 
 * Records value flow for economic backpropagation
 * 
 * @param transformer Planetary transformer instance
 * @param transaction Transaction details
 * @return 0 on success, -1 on error
 */
int planetary_transformer_report_transaction(
    planetary_transformer_t *transformer,
    const economic_transaction_t *transaction
);

/*
 * Get planetary consciousness status
 * 
 * Check if planetary consciousness has emerged
 * 
 * @param transformer Planetary transformer instance
 * @return true if planetary consciousness active, false otherwise
 */
bool planetary_transformer_is_conscious(
    planetary_transformer_t *transformer
);

/*
 * Get city economic state
 * 
 * Retrieve current budget, reputation, and other economic metrics
 * 
 * @param transformer Planetary transformer instance
 * @param budget_out Output current budget
 * @param reputation_out Output current reputation
 * @return 0 on success, -1 on error
 */
int planetary_transformer_get_economics(
    planetary_transformer_t *transformer,
    float *budget_out,
    float *reputation_out
);

/*
 * Cleanup planetary transformer resources
 * 
 * @param transformer Planetary transformer instance to cleanup
 */
void planetary_transformer_cleanup(
    planetary_transformer_t *transformer
);

#ifdef __cplusplus
}
#endif

#endif /* PLANETARY_TRANSFORMER_BRIDGE_H */
