# War Theatre Simulator

This is a project of turn-based simulation of strategic millitary combats on a hexagonal map. There are three types of units and several biomes. Effectiveness of an attack depends of supply level and terrain type.

## Units
There are 3 types of units: infantry, tanks and artillery. They differ by damage dealt to other units, range and movement points.

Two most important parameters of a unit is **organization** and **supply level**.

### Organization
Organization is the potential to defend and attack (similar to HP in many games). During an attack, the enemy suffers organization loss equal to damage. If after an attack a unit has 0 or less organization, it is destroyed.

### Supply level
Unit that has low supply level deals little damage and having less than 25 prevents it from attacking. Every round all units are given 25 supply level points.

### Movement points
Movement to adjacent field or attacking costs 1 movement point. Renewed every turn. This value cannot be lower than 0.

## Controlling
This project has command line interface. Enter _h_ to get list of available commands.

## Example
For an example, please refer to _test/example1.cpp_ and its corresponding png map (it uses NATO symbols). It creates a map using _MapEditor_ class with two human factions and then runs the game. You can build it with:

```
cmake .
make example1
```
