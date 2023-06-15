#include "flecs.h"

#include <stdio.h>

typedef struct fl_comp_pos {
	float x;
	float y;
} fl_comp_pos_t;

typedef struct fl_comp_chunk_position {
	short int x;
	short int y;
} fl_comp_chunk_position_t;

typedef struct fl_comp_color {
	float r;
	float g;
	float b;
	float a;
} fl_comp_color_t;

typedef struct fl_comp_rect {
	float x;
	float y;
	float width;
	float height;
} fl_comp_rect_t;

ECS_COMPONENT_DECLARE(fl_comp_pos_t);
ECS_COMPONENT_DECLARE(fl_comp_chunk_position_t);
ECS_COMPONENT_DECLARE(fl_comp_color_t);
ECS_COMPONENT_DECLARE(fl_comp_rect_t);

void create_entities_in_system(ecs_iter_t* it) {
	ecs_world_t* world = it->world;

	ecs_entity_t parent = ecs_new(world, 0);
	ecs_set(world, parent, fl_comp_chunk_position_t, {0, 0});

	for (size_t i = 0; i < 30000000; i++) {
		ecs_entity_t entity = ecs_new(world, 0);
		ecs_set(world, entity, fl_comp_pos_t, {0.0F, 0.0F});
		ecs_set(world, entity, fl_comp_rect_t, {0.0F, 0.0F, 0.0F, 0.0F});
		ecs_set(world, entity, fl_comp_color_t, {0.0F, 0.0F, 0.0F, 0.0F});
		ecs_add_pair(world, EcsChildOf, entity, parent);
	}
}

int main() {
	ecs_world_t* world = ecs_init();

	ECS_COMPONENT_DEFINE(world, fl_comp_pos_t)
	ECS_COMPONENT_DEFINE(world, fl_comp_chunk_position_t)
	ECS_COMPONENT_DEFINE(world, fl_comp_color_t)
	ECS_COMPONENT_DEFINE(world, fl_comp_rect_t)

	ECS_TAG(world, CountableEntity)

	ecs_entity_t parent = ecs_new(world, CountableEntity);
	ecs_set(world, parent, fl_comp_chunk_position_t, {0, 0});

	for (size_t i = 0; i < 30000000; i++) {
		ecs_entity_t entity = ecs_new(world, CountableEntity);
		ecs_set(world, entity, fl_comp_pos_t, {0.0F, 0.0F});
		ecs_set(world, entity, fl_comp_rect_t, {0.0F, 0.0F, 0.0F, 0.0F});
		ecs_set(world, entity, fl_comp_color_t, {0.0F, 0.0F, 0.0F, 0.0F});

		ecs_add_pair(world, entity, EcsChildOf, parent);
	}

	printf("CountableEntity count: %d\n", ecs_count(world, CountableEntity));

	ECS_SYSTEM(world, create_entities_in_system, EcsOnStart, 0)

	ecs_progress(world, 0);

	printf("CountableEntity count: %d\n", ecs_count(world, CountableEntity));

	ecs_fini(world);

	return 0;
}
