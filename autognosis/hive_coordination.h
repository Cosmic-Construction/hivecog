#ifndef __HIVE_COORDINATION_H
#define __HIVE_COORDINATION_H

#include "autognosis.h"
#include <stdint.h>

// Hive message types for coordination
typedef enum {
    HIVE_MSG_HEARTBEAT,
    HIVE_MSG_KNOWLEDGE_SHARE,
    HIVE_MSG_HEALING_REQUEST,
    HIVE_MSG_HEALING_RESPONSE,
    HIVE_MSG_TOPOLOGY_UPDATE,
    HIVE_MSG_EMERGENCY_SIGNAL
} hive_message_type_t;

// Hive message structure
typedef struct hive_message {
    uint32_t sender_id;
    uint32_t recipient_id;  // 0 for broadcast
    hive_message_type_t type;
    uint32_t sequence_number;
    time_t timestamp;
    uint32_t data_length;
    char data[512];
} hive_message_t;

// Knowledge sharing structure
typedef struct knowledge_packet {
    char atom_name[256];
    atom_type_t atom_type;
    float truth_value;
    float confidence;
    float importance;
    time_t timestamp;
} knowledge_packet_t;

// Healing coordination
typedef struct healing_request {
    uint32_t problem_id;
    char problem_description[256];
    float severity;
    uint32_t requesting_node;
    time_t request_time;
    healing_action_t suggested_action;
} healing_request_t;

typedef struct healing_response {
    uint32_t problem_id;
    uint32_t responding_node;
    healing_action_t recommended_action;
    float confidence;
    char additional_info[128];
} healing_response_t;

// Hive coordination engine
typedef struct hive_coordinator {
    autognosis_engine_t *local_engine;
    uint32_t node_id;
    uint32_t sequence_counter;
    
    // Message handling
    void (*send_message)(struct hive_coordinator *, hive_message_t *);
    void (*receive_message)(struct hive_coordinator *, hive_message_t *);
    
    // Knowledge coordination
    void (*share_knowledge)(struct hive_coordinator *, atom_t *);
    void (*process_shared_knowledge)(struct hive_coordinator *, knowledge_packet_t *);
    
    // Healing coordination
    void (*request_healing_assistance)(struct hive_coordinator *, healing_request_t *);
    void (*respond_to_healing_request)(struct hive_coordinator *, healing_request_t *);
    
    // Collective intelligence
    void (*update_collective_knowledge)(struct hive_coordinator *);
    float (*calculate_swarm_health)(struct hive_coordinator *);
    
    // State
    time_t last_heartbeat;
    time_t last_knowledge_sync;
    float collective_intelligence_score;
    
} hive_coordinator_t;

// Core functions
hive_coordinator_t* hive_coordinator_create(autognosis_engine_t *engine, uint32_t node_id);
void hive_coordinator_destroy(hive_coordinator_t *coordinator);
void hive_coordinator_process_cycle(hive_coordinator_t *coordinator);

// Message functions
hive_message_t* hive_message_create(uint32_t sender, uint32_t recipient, hive_message_type_t type);
void hive_message_destroy(hive_message_t *message);
void hive_message_set_data(hive_message_t *message, const void *data, uint32_t length);

// Knowledge sharing functions
knowledge_packet_t* knowledge_packet_from_atom(atom_t *atom);
atom_t* knowledge_packet_to_atom(atom_space_t *space, knowledge_packet_t *packet);
void hive_broadcast_knowledge(hive_coordinator_t *coordinator, atom_t *atom);

// Healing coordination functions
healing_request_t* healing_request_create(const char *problem_desc, float severity, uint32_t node_id);
healing_response_t* healing_response_create(uint32_t problem_id, uint32_t node_id, healing_action_t action, float confidence);
void hive_coordinate_healing(hive_coordinator_t *coordinator, const char *problem_desc);

// Collective intelligence functions
void hive_update_collective_topology(hive_coordinator_t *coordinator);
float hive_calculate_emergence_factor(hive_coordinator_t *coordinator);
void hive_adaptive_behavior_update(hive_coordinator_t *coordinator);

#endif /* __HIVE_COORDINATION_H */