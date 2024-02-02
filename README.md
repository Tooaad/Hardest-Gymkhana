# 🏃Hardest Gymkhana

**Dynamic Programming exercise** where I needed to find the best solution given a formula to find the minimum path.

## Subject
The production team of a TV show has launched a gymkhana competition in which the contestants have to overcome crazy obstacles to win one million dollars. 
The show's rules establish that contestants have to run through a building with several floors. At each level, there is a sequence of obstacles. All levels have the same number of obstacles. Levels are connected by stairs at the end of each obstacle. 

![](https://i.imgur.com/KYMEo37.gif)

Contestants can go upstairs and downstairs to any floor they want. Contestants have 2 states, they can make the obstacles at max speed, or half speed, if they decide to do it this way, the time it will take will be twice as long. Contestants cannot make two consecutive obstacles at max speed.

## Input
```javascript
// Number of floors - Obstacles
4 6
// Obstacles
112 49 96 98 81 50
96 55 108 90 66 73
109 48 93 105 81 74
100 55 90 92 65 68

// Another competition
// Number of floors - Obstacles
1 55
// Obstacles
98 76 61 94 67 98 9 34 16 78 106 76 61 94 67 98 9 34 16 78 106 76 61 94 67 98 9 34 16 78 106 76 61 94 67 98 9 34 16 78 106 76 61 94 67 98 9 34 16 78 106 76 61 94 67 

// Delimiter
0 0
```

## Approach
As I was asked to solve this with a Dynamic Programming solution, I split the problem into two parts, find the shortest path, and get the optimal speed. Although the **optimal approach would be a memoizing algorithm**. **I used a recursive tree** to find the best optimal speed for the formula I had to discover.

## Usage
`$ make && ./program.run < input.txt`

