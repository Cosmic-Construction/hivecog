#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "hive_coordination.h"

// Static function declarations
static void send_message_impl(hive_coordinator_t *coordinator, hive_message_t *message);
static void receive_message_impl(hive_coordinator_t *coordinator, hive_message_t *message);
static void share_knowledge_impl(hive_coordinator_t *coordinator, atom_t *atom);
static void process_shared_knowledge_impl(hive_coordinator_t *coordinator, knowledge_packet_t *packet);
static void request_healing_assistance_impl(hive_coordinator_t *coordinator, healing_request_t *request);
static void respond_to_healing_request_impl(hive_coordinator_t *coordinator, healing_request_t *request);
static void update_collective_knowledge_impl(hive_coordinator_t *coordinator);
static float calculate_swarm_health_impl(hive_coordinator_t *coordinator);

// Message implementation
hive_message_t* hive_message_create(uint32_t sender, uint32_t recipient, hive_message_type_t type) {
    hive_message_t *message = calloc(1, sizeof(hive_message_t));
    if (!message) return NULL;
    
    message->sender_id = sender;
    message->recipient_id = recipient;
    message->type = type;
    message->sequence_number = 0;
    message->timestamp = time(NULL);
    message->data_length = 0;
    
    return message;
}

void hive_message_destroy(hive_message_t *message) {
    if (message) {
        free(message);
    }
}

void hive_message_set_data(hive_message_t *message, const void *data, uint32_t length) {
    if (!message || !data || length > sizeof(message->data)) return;
    
    memcpy(message->data, data, length);
    message->data_length = length;
}

// Knowledge sharing implementation
knowledge_packet_t* knowledge_packet_from_atom(atom_t *atom) {
    if (!atom) return NULL;
    
    knowledge_packet_t *packet = calloc(1, sizeof(knowledge_packet_t));
    if (!packet) return NULL;
    
    strncpy(packet->atom_name, atom->name, sizeof(packet->atom_name) - 1);
    packet->atom_type = atom->type;
    packet->truth_value = atom->truth_value;
    packet->confidence = atom->confidence;
    packet->importance = atom->importance;
    packet->timestamp = atom->timestamp;
    
    return packet;
}

atom_t* knowledge_packet_to_atom(atom_space_t *space, knowledge_packet_t *packet) {
    if (!space || !packet) return NULL;
    
    atom_t *atom = atomspace_add_atom(space, packet->atom_type, packet->atom_name);
    if (atom) {
        atomspace_update_truth_value(atom, packet->truth_value, packet->confidence);
        atom->importance = packet->importance;
        atom->timestamp = packet->timestamp;
    }
    
    return atom;
}

void hive_broadcast_knowledge(hive_coordinator_t *coordinator, atom_t *atom) {
    if (!coordinator || !atom) return;
    
    knowledge_packet_t *packet = knowledge_packet_from_atom(atom);
    if (packet) {
        hive_message_t *message = hive_message_create(coordinator->node_id, 0, HIVE_MSG_KNOWLEDGE_SHARE);
        if (message) {
            hive_message_set_data(message, packet, sizeof(knowledge_packet_t));
            coordinator->send_message(coordinator, message);
            hive_message_destroy(message);
        }
        free(packet);
    }
}

// Healing coordination implementation
healing_request_t* healing_request_create(const char *problem_desc, float severity, uint32_t node_id) {
    if (!problem_desc) return NULL;
    
    healing_request_t *request = calloc(1, sizeof(healing_request_t));
    if (!request) return NULL;
    
    static uint32_t problem_id_counter = 1;
    request->problem_id = problem_id_counter++;
    strncpy(request->problem_description, problem_desc, sizeof(request->problem_description) - 1);
    request->severity = severity;
    request->requesting_node = node_id;
    request->request_time = time(NULL);
    request->suggested_action = HEALING_NONE;
    
    return request;
}

healing_response_t* healing_response_create(uint32_t problem_id, uint32_t node_id, healing_action_t action, float confidence) {
    healing_response_t *response = calloc(1, sizeof(healing_response_t));
    if (!response) return NULL;
    
    response->problem_id = problem_id;
    response->responding_node = node_id;
    response->recommended_action = action;
    response->confidence = confidence;
    
    return response;
}

void hive_coordinate_healing(hive_coordinator_t *coordinator, const char *problem_desc) {
    if (!coordinator || !problem_desc) return;
    
    // Create healing request
    healing_request_t *request = healing_request_create(problem_desc, 0.8f, coordinator->node_id);
    if (request) {
        // First try local healing
        healing_action_t local_action = healing_evaluate_problem(coordinator->local_engine, problem_desc);
        request->suggested_action = local_action;
        
        // If local healing is insufficient, request hive assistance
        if (local_action == HEALING_NONE || local_action == HEALING_RETRY) {
            coordinator->request_healing_assistance(coordinator, request);
        }
        
        free(request);
    }
}

// Collective intelligence implementation
void hive_update_collective_topology(hive_coordinator_t *coordinator) {
    if (!coordinator) return;
    
    // Update knowledge about collective network state
    if (coordinator->local_engine && coordinator->local_engine->topology) {
        network_topology_t *topology = coordinator->local_engine->topology;
        
        // Create atoms representing collective state
        char collective_state[128];
        snprintf(collective_state, sizeof(collective_state), 
                "collective_health_%.2f", topology->overall_health);
        
        atom_t *collective_atom = atomspace_add_atom(
            coordinator->local_engine->global_knowledge, 
            ATOM_CONCEPT, 
            collective_state
        );
        
        if (collective_atom) {
            atomspace_update_truth_value(collective_atom, topology->overall_health, 0.9f);
        }
    }
}

float hive_calculate_emergence_factor(hive_coordinator_t *coordinator) {
    if (!coordinator || !coordinator->local_engine) return 0.0f;
    
    // Calculate emergence based on collective intelligence and network health
    float network_health = coordinator->local_engine->topology ? 
        coordinator->local_engine->topology->overall_health : 0.5f;
    
    float knowledge_diversity = coordinator->local_engine->global_knowledge ? 
        (float)coordinator->local_engine->global_knowledge->atom_count / 100.0f : 0.1f;
    
    if (knowledge_diversity > 1.0f) knowledge_diversity = 1.0f;
    
    // Emergence factor combines network health, knowledge diversity, and collective intelligence
    float emergence = (network_health * 0.4f) + 
                     (knowledge_diversity * 0.3f) + 
                     (coordinator->collective_intelligence_score * 0.3f);
    
    return emergence > 1.0f ? 1.0f : emergence;
}

void hive_adaptive_behavior_update(hive_coordinator_t *coordinator) {
    if (!coordinator) return;
    
    float emergence_factor = hive_calculate_emergence_factor(coordinator);
    
    // Adapt behavior based on emergence
    if (emergence_factor > 0.8f) {
        // High emergence: increase autonomous behavior
        coordinator->local_engine->self_image->autonomy_level = 0.9f;
    } else if (emergence_factor < 0.3f) {
        // Low emergence: increase coordination requests
        coordinator->local_engine->self_image->autonomy_level = 0.3f;
    }
    
    coordinator->collective_intelligence_score = emergence_factor;
}

// Core coordinator implementation
static void send_message_impl(hive_coordinator_t *coordinator, hive_message_t *message) {
    if (!coordinator || !message) return;
    
    // Set sequence number
    message->sequence_number = ++coordinator->sequence_counter;
    
    // In a real implementation, this would serialize and transmit the message
    // For now, we'll just log it
    printf("Hive: Node %u sending message type %d to %u (seq %u)\n", 
           coordinator->node_id, message->type, message->recipient_id, message->sequence_number);
}

static void receive_message_impl(hive_coordinator_t *coordinator, hive_message_t *message) {
    if (!coordinator || !message) return;
    
    printf("Hive: Node %u received message type %d from %u\n", 
           coordinator->node_id, message->type, message->sender_id);
    
    switch (message->type) {
        case HIVE_MSG_HEARTBEAT:
            // Update node in topology
            if (coordinator->local_engine && coordinator->local_engine->topology) {
                topology_add_node(coordinator->local_engine->topology, 
                                message->sender_id, "remote_node");
                topology_update_node_health(coordinator->local_engine->topology, 
                                          message->sender_id, 1.0f);
            }
            break;
            
        case HIVE_MSG_KNOWLEDGE_SHARE:
            if (message->data_length == sizeof(knowledge_packet_t)) {
                knowledge_packet_t *packet = (knowledge_packet_t *)message->data;
                coordinator->process_shared_knowledge(coordinator, packet);
            }
            break;
            
        case HIVE_MSG_HEALING_REQUEST:
            if (message->data_length == sizeof(healing_request_t)) {
                healing_request_t *request = (healing_request_t *)message->data;
                coordinator->respond_to_healing_request(coordinator, request);
            }
            break;
            
        case HIVE_MSG_TOPOLOGY_UPDATE:
            // Update collective topology
            hive_update_collective_topology(coordinator);
            break;
            
        case HIVE_MSG_EMERGENCY_SIGNAL:
            // Respond to emergency
            printf("Hive: Emergency signal received from node %u\n", message->sender_id);
            break;
            
        default:
            break;
    }
}

static void share_knowledge_impl(hive_coordinator_t *coordinator, atom_t *atom) {
    if (!coordinator || !atom) return;
    
    // Only share important knowledge
    if (atom->importance > 0.7f) {
        hive_broadcast_knowledge(coordinator, atom);
    }
}

static void process_shared_knowledge_impl(hive_coordinator_t *coordinator, knowledge_packet_t *packet) {
    if (!coordinator || !packet || !coordinator->local_engine) return;
    
    // Integrate shared knowledge into local knowledge base
    atom_t *local_atom = knowledge_packet_to_atom(
        coordinator->local_engine->global_knowledge, packet);
    
    if (local_atom) {
        printf("Hive: Integrated shared knowledge: %s (truth=%.2f)\n", 
               local_atom->name, local_atom->truth_value);
    }
}

static void request_healing_assistance_impl(hive_coordinator_t *coordinator, healing_request_t *request) {
    if (!coordinator || !request) return;
    
    hive_message_t *message = hive_message_create(coordinator->node_id, 0, HIVE_MSG_HEALING_REQUEST);
    if (message) {
        hive_message_set_data(message, request, sizeof(healing_request_t));
        coordinator->send_message(coordinator, message);
        hive_message_destroy(message);
    }
}

static void respond_to_healing_request_impl(hive_coordinator_t *coordinator, healing_request_t *request) {
    if (!coordinator || !request) return;
    
    // Evaluate the problem locally and provide recommendation
    healing_action_t recommended_action = healing_evaluate_problem(
        coordinator->local_engine, request->problem_description);
    
    healing_response_t *response = healing_response_create(
        request->problem_id, coordinator->node_id, recommended_action, 0.8f);
    
    if (response) {
        hive_message_t *message = hive_message_create(
            coordinator->node_id, request->requesting_node, HIVE_MSG_HEALING_RESPONSE);
        
        if (message) {
            hive_message_set_data(message, response, sizeof(healing_response_t));
            coordinator->send_message(coordinator, message);
            hive_message_destroy(message);
        }
        
        free(response);
    }
}

static void update_collective_knowledge_impl(hive_coordinator_t *coordinator) {
    if (!coordinator) return;
    
    hive_update_collective_topology(coordinator);
    hive_adaptive_behavior_update(coordinator);
}

static float calculate_swarm_health_impl(hive_coordinator_t *coordinator) {
    if (!coordinator || !coordinator->local_engine) return 0.0f;
    
    float local_health = coordinator->local_engine->self_image->health_score;
    float network_health = coordinator->local_engine->topology ? 
        coordinator->local_engine->topology->overall_health : 0.5f;
    
    // Swarm health is a weighted combination
    return (local_health * 0.3f) + (network_health * 0.4f) + 
           (coordinator->collective_intelligence_score * 0.3f);
}

hive_coordinator_t* hive_coordinator_create(autognosis_engine_t *engine, uint32_t node_id) {
    if (!engine) return NULL;
    
    hive_coordinator_t *coordinator = calloc(1, sizeof(hive_coordinator_t));
    if (!coordinator) return NULL;
    
    coordinator->local_engine = engine;
    coordinator->node_id = node_id;
    coordinator->sequence_counter = 0;
    
    // Set function pointers
    coordinator->send_message = send_message_impl;
    coordinator->receive_message = receive_message_impl;
    coordinator->share_knowledge = share_knowledge_impl;
    coordinator->process_shared_knowledge = process_shared_knowledge_impl;
    coordinator->request_healing_assistance = request_healing_assistance_impl;
    coordinator->respond_to_healing_request = respond_to_healing_request_impl;
    coordinator->update_collective_knowledge = update_collective_knowledge_impl;
    coordinator->calculate_swarm_health = calculate_swarm_health_impl;
    
    // Initialize state
    coordinator->last_heartbeat = time(NULL);
    coordinator->last_knowledge_sync = time(NULL);
    coordinator->collective_intelligence_score = 0.5f;
    
    return coordinator;
}

void hive_coordinator_destroy(hive_coordinator_t *coordinator) {
    if (coordinator) {
        free(coordinator);
    }
}

void hive_coordinator_process_cycle(hive_coordinator_t *coordinator) {
    if (!coordinator) return;
    
    time_t now = time(NULL);
    
    // Send periodic heartbeat
    if ((now - coordinator->last_heartbeat) >= 30) {
        hive_message_t *heartbeat = hive_message_create(
            coordinator->node_id, 0, HIVE_MSG_HEARTBEAT);
        
        if (heartbeat) {
            coordinator->send_message(coordinator, heartbeat);
            hive_message_destroy(heartbeat);
            coordinator->last_heartbeat = now;
        }
    }
    
    // Update collective knowledge
    if ((now - coordinator->last_knowledge_sync) >= 60) {
        coordinator->update_collective_knowledge(coordinator);
        coordinator->last_knowledge_sync = now;
    }
    
    // Share important local knowledge
    if (coordinator->local_engine && coordinator->local_engine->global_knowledge) {
        atom_t *current = coordinator->local_engine->global_knowledge->atoms;
        while (current) {
            if (current->importance > 0.8f && 
                (now - current->timestamp) < 300) { // Recent and important
                coordinator->share_knowledge(coordinator, current);
                break; // Share one at a time to avoid flooding
            }
            current = current->next;
        }
    }
}