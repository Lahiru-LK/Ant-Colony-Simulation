
# 🐜 Ant Colony Simulation

Welcome to the **Ant Colony Simulation** project! This program simulates the behavior of an ant colony, including their search for food and water, reproduction, and survival. Dive into the fascinating world of ants and see how they work together to thrive in their environment.

https://github.com/Lahiru-LK/Ant-Colony-Simulation/assets/104630433/8b66042a-6025-4aca-ba91-7aaacea96251


## 📂 Project Structure

The project consists of the following files:

- `main.c`: The entry point of the program.
- `colony.h`: Header file containing definitions and function declarations.
- `colony.c`: Source file implementing the functionality of the ant colony simulation.

## 🚀 Getting Started

### Prerequisites

- A C compiler (GCC recommended)
- Make sure you have the `unistd.h` library available on your system.

### Compilation

To compile the project, run:

```sh
gcc main.c colony.c -o ant_colony_simulation
```

### Running the Simulation

After compilation, run the program using:

```sh
./ant_colony_simulation
```

## 📝 How It Works

### 1. Initial Setup

The simulation starts by initializing the colony with a central position on a grid. Initially, there is one ant, and food and water resources are scattered around the colony.

```c
void initialize_colony(Colony *colony);
```

### 2. Simulation Loop

The simulation runs for a specified number of steps, where ants move around, search for resources, and return to the colony with food and water. The ants' behavior is controlled by the following functions:

```c
void move_ant(Ant *ant);
void search_for_resources(Colony *colony);
void simulate(Colony *colony, int steps);
```

### 3. Displaying the Colony

The current state of the colony, including the positions of ants, food, water, and the colony itself, is displayed on the screen:

```c
void display_colony(const Colony *colony);
```

## 🌟 Features

- **Dynamic Ant Movement**: Ants move randomly within a specified box around the colony.
- **Resource Collection**: Ants collect food and water when they encounter them.
- **Reproduction**: New ants are produced when an ant returns to the colony with both food and water.
- **Survival**: Ants have a small chance of dying each step, adding a survival aspect to the simulation.

## 📊 Dashboard

The simulation provides a dashboard that shows the live count of ants, dead ants, food, and water available.

```
Ant Colony Dashboard:
-----------------------
| Live Ant Count: 3   |
| Dead Ant Count: 1   |
| Birth Site Count: 2 |
| Food Count: 7       |
| Water Count: 6      |
-----------------------
```

## 🛠️ Code Highlights

### Colony Initialization

Ants, food, and water are initialized with random positions within a defined box:

```c
void initialize_colony(Colony *colony) {
    // Initialization logic...
}
```

### Ant Movement

Ants move randomly within the defined box and ensure they stay within bounds:

```c
void move_ant(Ant *ant) {
    // Movement logic...
}
```

### Resource Search and Collection

Ants search for and collect resources. When they return to the colony with resources, new ants can be produced:

```c
void search_for_resources(Colony *colony) {
    // Resource search and collection logic...
}
```

## 📬 Contributions

Feel free to contribute to this project by forking the repository, making changes, and submitting a pull request. Contributions are welcome!

## 📜 License

This project is licensed under the MIT License.

---

Enjoy exploring the world of ants with this simulation! 🐜🍂💧

