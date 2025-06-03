#include "../include/cJSON.h"
#include "goal.h"
#include "utils.h"

#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>

Goal** goal_init(const int n) {
	Goal** goals = malloc(n * sizeof *goals);
	if (goals == NULL) {
		printf("[MEMORY ERROR] Couldn't allocate enough memory for goals.\n");
		exit(1);
	}

	return goals;
}

SubGoal* goal_sub_create(const SubGoalType type, const char* name, const char* root_name, const DisplayType display_type, const int goal) {
	SubGoal* sub_goal = malloc(sizeof *sub_goal);
	if (sub_goal == NULL) {
		printf("[MEMORY ERROR] Couldn't allocate enough memory for a sub-goal.\n");
		exit(1);
	}

	sub_goal->name = malloc((strlen(name) + 1) * sizeof(char));
	if (sub_goal->name == NULL) {
		free(sub_goal);
		printf("[MEMORY ERROR] Couldn't allocate enough memory for sub-goal's name.\n");
		exit(1);
	}

	sub_goal->root_name = malloc((strlen(root_name) + 1) * sizeof(char));
	if (sub_goal->root_name == NULL) {
		free(sub_goal->name);
		free(sub_goal);
		printf("[MEMORY ERROR] Couldn't allocate enough memory for sub-goal's root name.\n");
		exit(1);
	}

	strcpy(sub_goal->name, name);
	strcpy(sub_goal->root_name, root_name);
	sub_goal->goal = goal;
	sub_goal->progress = 0;
	sub_goal->type = type;
	sub_goal->display_type = display_type;

	return sub_goal;
}

Goal* goal_create(const SDL_Renderer* renderer, const GoalType type, const cJSON *translation) {
	Goal* goal = malloc(sizeof * goal);
	if (goal == NULL) {
		goto memory_error;
	}

	goal->done = 0;

	char localisation_buffer[128];

	/*
	goaltext_shells
	goaltext_craft_conduit
	goaltext_place_conduit
	goaltext_hdwgh
	goaltext_done_hdwgh
	goaltext_trident
	goaltext_awaiting_thunder
	goaltext_done_thunder
	goaltext_skulls
	goaltext_done_skulls
	goaltext_heavy_core
	goaltext_mace
	goaltext_overkill
	goaltext_done_overkill
	goaltext_eggs
	goaltext_place_eggs
	goaltext_snifflet
	goaltext_done_sniffer
	goaltext_silence
	goaltext_done_silence
	*/

	switch (type) {
		case GOALTYPE_nautilus_shells:
			goal->icon_texture = check_sdl_ptr(IMG_LoadTexture(renderer, "resources/sprites/items/nautilus_shell.png"));
		
			goal->sub_goals_n = 5;
			goal->sub_goals = malloc(goal->sub_goals_n * sizeof *goal->sub_goals);
			if (goal->sub_goals == NULL) {
				goto memory_error;
			}

			load_localisation(localisation_buffer, "goaltext:shells", translation);
			goal->sub_goals[0] = goal_sub_create(SUBGOALTYPE_item_pick_up, localisation_buffer, "minecraft:nautilus_shell", DISPLAYTYPE_name_progress_goal, 8);

			load_localisation(localisation_buffer, "goaltext:craft_conduit", translation);
			goal->sub_goals[1] = goal_sub_create(SUBGOALTYPE_item_craft, localisation_buffer, "minecraft:conduit", DISPLAYTYPE_name, 1);

			load_localisation(localisation_buffer, "goaltext:place_conduit", translation);
			goal->sub_goals[2] = goal_sub_create(SUBGOALTYPE_item_use, localisation_buffer, "minecraft:conduit", DISPLAYTYPE_name, 1);

			load_localisation(localisation_buffer, "goaltext:hdwgh", translation);
			goal->sub_goals[3] = goal_sub_create(SUBGOALTYPE_advancement, localisation_buffer, "minecraft:nether/all_effects", DISPLAYTYPE_name, 1);

			load_localisation(localisation_buffer, "goaltext:done_hdwgh", translation);
			goal->sub_goals[4] = goal_sub_create(SUBGOALTYPE_final, localisation_buffer, "", DISPLAYTYPE_name, -1);

			break;

		case GOALTYPE_trident:
			goal->icon_texture = check_sdl_ptr(IMG_LoadTexture(renderer, "resources/sprites/items/trident.png"));
			
			goal->sub_goals_n = 4;
			goal->sub_goals = malloc(goal->sub_goals_n * sizeof * goal->sub_goals);
			if (goal->sub_goals == NULL) {
				goto memory_error;
			}

			load_localisation(localisation_buffer, "goaltext:trident", translation);
			goal->sub_goals[0] = goal_sub_create(SUBGOALTYPE_item_pick_up, localisation_buffer, "minecraft:trident", DISPLAYTYPE_name, 1);

			load_localisation(localisation_buffer, "goaltext:awaiting_thunder", translation);
			goal->sub_goals[1] = goal_sub_create(SUBGOALTYPE_advancement, localisation_buffer, "minecraft:adventure/very_very_frightening", DISPLAYTYPE_name, 1);
			
			load_localisation(localisation_buffer, "goaltext:awaiting_thunder", translation);
			goal->sub_goals[2] = goal_sub_create(SUBGOALTYPE_advancement, localisation_buffer, "minecraft:adventure/lightning_rod_with_villager_no_fire", DISPLAYTYPE_name, 1);
			
			load_localisation(localisation_buffer, "goaltext:done_thunder", translation);
			goal->sub_goals[3] = goal_sub_create(SUBGOALTYPE_final, localisation_buffer, "", DISPLAYTYPE_name, -1);
			
			break;

		case GOALTYPE_wither_skulls:
			goal->icon_texture = check_sdl_ptr(IMG_LoadTexture(renderer, "resources/sprites/items/wither_skeleton_skull.png"));

			goal->sub_goals_n = 2;
			goal->sub_goals = malloc(goal->sub_goals_n * sizeof * goal->sub_goals);
			if (goal->sub_goals == NULL) {
				goto memory_error;
			}

			load_localisation(localisation_buffer, "goaltext:skulls", translation);
			goal->sub_goals[0] = goal_sub_create(SUBGOALTYPE_item_pick_up, localisation_buffer, "minecraft:wither_skeleton_skull", DISPLAYTYPE_name_progress_goal, 3);
			
			load_localisation(localisation_buffer, "goaltext:done_skulls", translation);
			goal->sub_goals[1] = goal_sub_create(SUBGOALTYPE_kill, localisation_buffer, "minecraft:wither_skeleton", DISPLAYTYPE_name_progress, -1);
			
			break;

		case GOALTYPE_heavy_core:
			goal->icon_texture = check_sdl_ptr(IMG_LoadTexture(renderer, "resources/sprites/items/mace.png"));

			goal->sub_goals_n = 4;
			goal->sub_goals = malloc(goal->sub_goals_n * sizeof * goal->sub_goals);
			if (goal->sub_goals == NULL) {
				goto memory_error;
			}

			load_localisation(localisation_buffer, "goaltext:heavy_core", translation);
			goal->sub_goals[0] = goal_sub_create(SUBGOALTYPE_item_pick_up, localisation_buffer, "minecraft:heavy_core", DISPLAYTYPE_name, 1);
			
			load_localisation(localisation_buffer, "goaltext:mace", translation);
			goal->sub_goals[1] = goal_sub_create(SUBGOALTYPE_item_craft, localisation_buffer, "minecraft:mace", DISPLAYTYPE_name, 1);
			
			load_localisation(localisation_buffer, "goaltext:overkill", translation);
			goal->sub_goals[2] = goal_sub_create(SUBGOALTYPE_advancement, localisation_buffer, "minecraft:adventure/overoverkill", DISPLAYTYPE_name, 1);
			
			load_localisation(localisation_buffer, "goaltext:done_overkill", translation);
			goal->sub_goals[3] = goal_sub_create(SUBGOALTYPE_item_use, localisation_buffer, "minecraft:ominous_trial_key", DISPLAYTYPE_name_progress, -1);
			
			break;

		case GOALTYPE_sniffers:
			goal->icon_texture = check_sdl_ptr(IMG_LoadTexture(renderer, "resources/sprites/items/sniffer_egg.png"));

			goal->sub_goals_n = 4;
			goal->sub_goals = malloc(goal->sub_goals_n * sizeof * goal->sub_goals);
			if (goal->sub_goals == NULL) {
				goto memory_error;
			}

			load_localisation(localisation_buffer, "goaltext:eggs", translation);
			goal->sub_goals[0] = goal_sub_create(SUBGOALTYPE_item_pick_up, localisation_buffer, "minecraft:sniffer_egg", DISPLAYTYPE_name_progress_goal, 2);
			
			load_localisation(localisation_buffer, "goaltext:place_eggs", translation);
			goal->sub_goals[1] = goal_sub_create(SUBGOALTYPE_item_use, localisation_buffer, "minecraft:sniffer_egg", DISPLAYTYPE_name, 2);
			
			load_localisation(localisation_buffer, "goaltext:snifflet", translation);
			goal->sub_goals[2] = goal_sub_create(SUBGOALTYPE_advancement, localisation_buffer, "minecraft:husbandry/feed_snifflet", DISPLAYTYPE_name, 1);
			
			load_localisation(localisation_buffer, "goaltext:done_sniffer", translation);
			goal->sub_goals[3] = goal_sub_create(SUBGOALTYPE_final, localisation_buffer, "", DISPLAYTYPE_name, -1);
			
			break;

		case GOALTYPE_silence:
			goal->icon_texture = check_sdl_ptr(IMG_LoadTexture(renderer, "resources/sprites/items/silence_trim.png"));

			goal->sub_goals_n = 2;
			goal->sub_goals = malloc(goal->sub_goals_n * sizeof * goal->sub_goals);
			if (goal->sub_goals == NULL) {
				goto memory_error;
			}

			load_localisation(localisation_buffer, "goaltext:silence", translation);
			goal->sub_goals[0] = goal_sub_create(SUBGOALTYPE_advancement, localisation_buffer, "minecraft:recipes/misc/silence_armor_trim_smithing_template", DISPLAYTYPE_name, 1);
			
			load_localisation(localisation_buffer, "goaltext:done_silence", translation);
			goal->sub_goals[1] = goal_sub_create(SUBGOALTYPE_final, localisation_buffer, "", DISPLAYTYPE_name, -1);
			
			break;
	
		default:
			return NULL;
	}

	// minecraft:recipes/misc/silence_armor_trim_smithing_template

	return goal;

memory_error:
	printf("[MEMORY ERROR] Couldn't allocate enough memory to create a new goal.\n");	
	exit(1);
}

void goal_update(Goal** goals, const int goals_n, const char* file_path) {
	cJSON* data = cJSON_from_file(file_path);
	if (!data) {
		return;
	}

	cJSON* stats = cJSON_GetObjectItemCaseSensitive(data, "stats");
	if (!stats) {
		return;
	}

	cJSON* picked_up = cJSON_GetObjectItemCaseSensitive(stats, "minecraft:picked_up");
	cJSON* crafted = cJSON_GetObjectItemCaseSensitive(stats, "minecraft:crafted");
	cJSON* used = cJSON_GetObjectItemCaseSensitive(stats, "minecraft:used");
	cJSON* killed = cJSON_GetObjectItemCaseSensitive(stats, "minecraft:killed");

	for (int i = 0; i < goals_n; ++i) {
		Goal* goal = goals[i];
		// if (goal->done) continue;
		int sub_goals_n = goal->sub_goals_n;

		for (int j = 0; j < sub_goals_n; ++j) {
			SubGoal* sub_goal = goal->sub_goals[j];
			
			if (sub_goal->progress >= sub_goal->goal) {
				if (j + 1 == sub_goals_n) {
					goal->done = 1;
				}

				// continue;
			}

			switch (sub_goal->type) {
				case SUBGOALTYPE_item_pick_up: {
					cJSON* value = cJSON_GetObjectItemCaseSensitive(picked_up, sub_goal->root_name);
					if (value && value->valueint) {
						sub_goal->progress = value->valueint;
					} else {
						sub_goal->progress = 0;
						goal->done = 0;
					}
					break;
				}
			
				case SUBGOALTYPE_item_craft: {
					cJSON* value = cJSON_GetObjectItemCaseSensitive(crafted, sub_goal->root_name);
					if (value && value->valueint) {
						sub_goal->progress = value->valueint;
					} else {
						sub_goal->progress = 0;
						goal->done = 0;
					}
					break;
				}

				case SUBGOALTYPE_item_use: {
					cJSON* value = cJSON_GetObjectItemCaseSensitive(used, sub_goal->root_name);
					if (value && value->valueint) {
						sub_goal->progress = value->valueint;
					} else {
						sub_goal->progress = 0;
						goal->done = 0;
					}
					break;
				}

				/*case SUBGOALTYPE_advancement: { // ADV_update_advancements handles the advancement case.
					for (int i = 0; i < adv_n; ++i) {
						if (strcmp(adv[i]->root_name, sub_goal->root_name) == 0) {
							sub_goal->progress = adv[i]->done;
						}
					}
					break;
				}*/

				case SUBGOALTYPE_kill: {
					cJSON* value = cJSON_GetObjectItemCaseSensitive(killed, sub_goal->root_name);
					if (value && value->valueint) {
						sub_goal->progress = value->valueint;
					} else {
						sub_goal->progress = 0;
						goal->done = 0;
					}
					break;
				}
			
				default:
					break;
			}
		}
	}

	cJSON_Delete(data);
}

void goal_delete(Goal** goals, const int goals_n) {
	for (int i = 0; i < goals_n; ++i) {
		Goal* goal = goals[i];
		SDL_DestroyTexture(goal->icon_texture);

		for (int j = 0; j < goal->sub_goals_n; ++j) {
			SubGoal* sub_goal = goal->sub_goals[j];
			free(sub_goal->name);
			free(sub_goal->root_name);
		}

		free(goal->sub_goals);
		free(goal);
	}

	free(goals);
}
