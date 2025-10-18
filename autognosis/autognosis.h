#ifndef __AUTOGNOSIS_H
#define __AUTOGNOSIS_H

#include <stdint.h>
#include <time.h>

// Forward declarations
struct atom_space;
struct hive_node;
struct network_topology;

// AtomSpace-inspired knowledge representation
typedef enum {
    ATOM_NODE,
    ATOM_LINK,
    ATOM_CONCEPT,
    ATOM_PREDICATE,
    ATOM_EVALUATION
} atom_type_t;

typedef struct atom {
    uint32_t id;
    atom_type_t type;
    char name[256];
    float truth_value;
    float confidence;
    float importance;
    time_t timestamp;
    struct atom *next;
    struct atom **outgoing;  // For links to other atoms
    int outgoing_count;
} atom_t;

typedef struct atom_space {
    atom_t *atoms;
    uint32_t atom_count;
    uint32_t next_id;
    struct hive_node *owner_node;
} atom_space_t;

// Self-image components
typedef struct self_image {
    atom_space_t *knowledge_base;
    struct network_topology *topology_view;
    float health_score;
    float autonomy_level;
    time_t last_update;
    char identity[64];
    uint32_t capabilities_mask;
} self_image_t;

// Network topology awareness
typedef struct network_node {
    uint32_t node_id;
    char address[64];
    float health_score;
    float trust_level;
    time_t last_seen;
    uint32_t capabilities;
    struct network_node *next;
} network_node_t;

typedef struct network_topology {
    network_node_t *nodes;
    uint32_t node_count;
    float overall_health;
    time_t last_update;
} network_topology_t;

// Autogenetic healing capabilities
typedef enum {
    HEALING_NONE,
    HEALING_RETRY,
    HEALING_REROUTE,
    HEALING_RECONSTRUCT,
    HEALING_MIGRATE
} healing_action_t;

typedef struct healing_rule {
    char condition[256];
    healing_action_t action;
    float confidence;
    uint32_t success_count;
    uint32_t attempt_count;
    struct healing_rule *next;
} healing_rule_t;

typedef struct autognosis_engine {
    self_image_t *self_image;
    network_topology_t *topology;
    healing_rule_t *healing_rules;
    atom_space_t *global_knowledge;
    
    // Cognitive processes
    void (*update_self_image)(struct autognosis_engine *);
    void (*process_network_events)(struct autognosis_engine *, void *event);
    healing_action_t (*diagnose_and_heal)(struct autognosis_engine *, void *problem);
    void (*share_knowledge)(struct autognosis_engine *, struct hive_node *);
    
    // State
    int running;
    time_t last_cognitive_cycle;
    float cognitive_load;
} autognosis_engine_t;

// Core functions
autognosis_engine_t* autognosis_create(const char *node_identity);
void autognosis_destroy(autognosis_engine_t *engine);
void autognosis_cognitive_cycle(autognosis_engine_t *engine);
void autognosis_process_hive_message(autognosis_engine_t *engine, void *message);
int autognosis_start(autognosis_engine_t *engine);
void autognosis_stop(autognosis_engine_t *engine);

// AtomSpace functions
atom_space_t* atomspace_create(void);
void atomspace_destroy(atom_space_t *space);
atom_t* atomspace_add_atom(atom_space_t *space, atom_type_t type, const char *name);
atom_t* atomspace_find_atom(atom_space_t *space, const char *name);
void atomspace_update_truth_value(atom_t *atom, float truth, float confidence);

// Self-image functions
self_image_t* self_image_create(const char *identity);
void self_image_destroy(self_image_t *image);
void self_image_update_health(self_image_t *image, float health);
void self_image_add_capability(self_image_t *image, uint32_t capability);

// Network topology functions
network_topology_t* topology_create(void);
void topology_destroy(network_topology_t *topology);
void topology_add_node(network_topology_t *topology, uint32_t id, const char *address);
void topology_update_node_health(network_topology_t *topology, uint32_t id, float health);
network_node_t* topology_find_healthiest_node(network_topology_t *topology);

// Healing functions
healing_rule_t* healing_create_rule(const char *condition, healing_action_t action, float confidence);
void healing_add_rule(autognosis_engine_t *engine, healing_rule_t *rule);
healing_action_t healing_evaluate_problem(autognosis_engine_t *engine, const char *problem_desc);
void healing_execute_action(autognosis_engine_t *engine, healing_action_t action, void *context);

#endif /* __AUTOGNOSIS_H */