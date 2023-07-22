#include <stdio.h>
#include <stdbool.h>

#define MAX_CAPACITY 3

int stt = 0;

typedef struct {
    int state[MAX_CAPACITY];
} State;

bool is_target_state(State state, int target, int vase) {
        if (state.state[vase] == target) {
            return true;
        }
    return false;
}

bool is_valid_state(State state) {
    for (int i = 0; i < MAX_CAPACITY; i++) {
        if (state.state[i] < 0 || state.state[i] > 10) {
            return false;
        }
    }
    return true;
}

bool is_duplicate_state(State state, State* visited_states, int num_visited_states) {
    for (int i = 0; i < num_visited_states; i++) {
        bool is_same = true;
        for (int j = 0; j < MAX_CAPACITY; j++) {
            if (state.state[j] != visited_states[i].state[j]) {
                is_same = false;
                break;
            }
        }
        if (is_same) {
            return true;
        }
    }
    return false;
}

void print_solution(State* visited_states, int num_visited_states) {
    printf("digraph G {\n");
    for (int i = 0; i < num_visited_states - 1; i++) {
        printf("\"(%d, %d, %d)\" -> ", visited_states[i].state[0], visited_states[i].state[1], visited_states[i].state[2]);
    }
    printf("\"(%d, %d, %d)\"", visited_states[num_visited_states - 1].state[0], visited_states[num_visited_states - 1].state[1], visited_states[num_visited_states - 1].state[2]);  
    printf("\n}");
}


void pour_water_dfs(State state, State* visited_states, int num_visited_states, int target, int vase) {
    if (is_duplicate_state(state, visited_states, num_visited_states) || !is_valid_state(state)) {
        return;
    }

    visited_states[num_visited_states] = state;
    num_visited_states++;

    if (is_target_state(state, target, vase) && stt == 0) {
        print_solution(visited_states, num_visited_states);
        stt = 1;
        return;
    }

    State new_state;

    // Pour water from jug 7l to jug 4l
    if (state.state[1] > 0 && state.state[0] < 10) {
        int pour_amount = (state.state[1] > 10 - state.state[0]) ? (10 - state.state[0]) : state.state[1];
        new_state.state[0] = state.state[0] + pour_amount;
        new_state.state[1] = state.state[1] - pour_amount;
        new_state.state[2] = state.state[2];
        pour_water_dfs(new_state, visited_states, num_visited_states, target, vase);
    }

    // Pour water from jug 7l to jug 4l
    if (state.state[1] > 0 && state.state[2] < 4) {
        int pour_amount = (state.state[1] > 4 - state.state[2]) ? (4 - state.state[2]) : state.state[1];
        new_state.state[0] = state.state[0];
        new_state.state[1] = state.state[1] - pour_amount;
        new_state.state[2] = state.state[2] + pour_amount;
        pour_water_dfs(new_state, visited_states, num_visited_states, target, vase);
    }

    // Pour water from jug 10l to jug 7l
    if (state.state[0] > 0 && state.state[1] < 7) {
        int pour_amount = (state.state[0] > 7 - state.state[1]) ? (7 - state.state[1]) : state.state[0];
        new_state.state[0] = state.state[0] - pour_amount;
        new_state.state[1] = state.state[1] + pour_amount;
        new_state.state[2] = state.state[2];
        pour_water_dfs(new_state, visited_states, num_visited_states, target, vase);
    }

    // Pour water from jug 10l to jug 4l
    if (state.state[0] > 0 && state.state[2] < 4) {
        int pour_amount = (state.state[0] > 4 - state.state[2]) ? (4 - state.state[2]) : state.state[0];
        new_state.state[0] = state.state[0] - pour_amount;
        new_state.state[1] = state.state[1];
        new_state.state[2] = state.state[2] + pour_amount;
        pour_water_dfs(new_state, visited_states, num_visited_states, target, vase);
    }

    // Pour water from jug 4l to jug 7l
    if (state.state[2] > 0 && state.state[1] < 7) {
        int pour_amount = (state.state[2] > 7 - state.state[1]) ? (7 - state.state[1]) : state.state[2];
        new_state.state[0] = state.state[0];
        new_state.state[1] = state.state[1] + pour_amount;
        new_state.state[2] = state.state[2] - pour_amount;
        pour_water_dfs(new_state, visited_states, num_visited_states, target, vase);
    }

    // Pour water from jug 4l to jug 10l
    if (state.state[2] > 0 && state.state[0] < 10) {
        int pour_amount = (state.state[2] > 10 - state.state[0]) ? (10 - state.state[0]) : state.state[2];
        new_state.state[0] = state.state[0] + pour_amount;
        new_state.state[1] = state.state[1];
        new_state.state[2] = state.state[2] - pour_amount;
        pour_water_dfs(new_state, visited_states, num_visited_states, target, vase);
    }

}

int main() {
    int target = 2;
    State initial_state = {0, 7, 4};
    State visited_states[100];
    int num_visited_states = 0;

    printf("Nhập bình muốn đạt được 2l nước(1 la binh 7l, 2 la binh 4l): ");
    int vase;
    scanf("%d", &vase);
    printf("\n");

    pour_water_dfs(initial_state, visited_states, num_visited_states, target, vase);

    return 0;
}
