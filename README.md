# Travelling Salesperson Problem (TSP) Solver

This project was developed for the **Desenho de Algoritmos** (Algorithm Design) course (2023-2024) at **FEUP**. It focuses on analyzing and solving the Travelling Salesperson Problem (TSP) using both exact and **heuristic methods**. The project explores trade-offs between optimality and efficiency, leveraging real-world datasets related to ocean shipping and urban delivery scenarios.

## Overview

The Travelling Salesperson Problem (TSP) is a classic optimization problem in computational theory, where the goal is to find the shortest route that visits each node exactly once and returns to the starting point. This project implements both **exact algorithms** (using backtracking) and **heuristic approaches** to address the computational intractability of TSP, particularly for large graphs. The solution is designed to work with various datasets, including real-world examples of shipping routes and urban delivery points.

## Features

- **Backtracking Algorithm**: An exact approach for small graphs, showcasing the computational infeasibility for larger datasets.
- **Triangular Approximation Heuristic**: A 2-approximation algorithm based on the triangle inequality, ensuring near-optimal solutions.
- **Custom Heuristic Algorithm**: A fast, efficient heuristic designed to work on large graphs, emphasizing practical performance.
- **Real-World Graph Handling**: Support for non-fully connected graphs, addressing challenges in real-world routing scenarios.
- **User-Friendly Interface**: An interactive menu for dataset selection, algorithm execution, and visualization of results.
- **Comprehensive Analysis**: Comparative evaluation of algorithms in terms of runtime, efficiency, and solution quality.

## Architecture

The project is structured to ensure modularity and extensibility, leveraging classes to encapsulate key functionalities:

### Core Components

- **Graph**: Represents the nodes and edges of the TSP problem, supporting both fully connected and sparse graphs.
- **DataManager**: Implements the asked functions that uses the algorithms to solve the TSP problem with different approaches.
- **Menu**: Provides a command-line interface for dataset selection, algorithm configuration, and result visualization.

### Dataset and Graph Representation

The project works with multiple datasets, including:
- **Small Test Graphs**: Designed for validating algorithms and observing execution feasibility.
- **Urban Delivery Data**: Represents delivery points in a city, with realistic graph structures.
- **Ocean Shipping Routes**: Models shipping routes between harbors, featuring sparse connectivity.

Graphs are represented using adjacency matrices or adjacency lists, depending on the algorithm requirements. Real-world datasets may include geographic coordinates, requiring Haversine distance calculations to derive edge weights dynamically.

## Algorithms

### 1. Backtracking Algorithm

- **Description**: Finds the exact solution to the TSP by exploring all possible routes.
- **Use Case**: Suitable for small graphs due to exponential runtime.
- **Output**: The shortest possible route and its total distance.
- **Visualization**: Execution time plotted for small and large datasets, highlighting computational infeasibility for larger graphs.

### 2. Triangular Approximation Heuristic

- **Description**: A 2-approximation algorithm leveraging the triangle inequality.
- **Use Case**: Provides a near-optimal solution efficiently for fully connected graphs.
- **Output**: A feasible route and its total distance, compared with the backtracking solution for validation on small graphs.
- **Special Handling**: Assumes all graphs are fully connected, using Haversine distance for missing edges.

### 3. Custom Heuristic

- **Description**: A heuristic algorithm designed for large graphs, focusing on execution speed while maintaining solution quality.
- **Strategies**: May include clustering, divide-and-conquer, or advanced graph traversal techniques.
- **Output**: A feasible route and its total distance, compared against the triangular approximation for runtime and quality.

### 4. Real-World Solver

- **Description**: An algorithm designed for non-fully connected graphs, starting from a user-defined node.
- **Use Case**: Handles sparse graphs with real-world constraints, ensuring feasible solutions when possible.
- **Output**: A route (or an error message if no route exists), with an analysis of the challenges and trade-offs.

### Authors
- Diogo Ramos (up202207954)
- Gabriel Braga (up202207784)
- Guilherme Rego (up202207041)
