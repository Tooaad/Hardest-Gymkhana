# 🏃Hardest Gymkhana

Dynamic Programming exercise where we needed to find the best solution given a formula to find the minimum path.

## Subject
The production team of a TV show have launched a gymkhana competition in which the contestants have to overcome crazy obstacles in order to win one million dollars. 
The rules of the show establish that contestants have to run through a building that have  several floors. In each level there is a sequence of obstacles. All levels have the same number of obstacles. Levels are connected by stairs at the end of each obstacle. 

![](https://i.gyazo.com/95adfd69a7a0e4863be76e09b2a5a15f.png)

Contestans can go upstairs and downstairs to any floor they want. Contestans have 2 states, they can make the obstacles at max speed, or half speed, if they decide to do it this way, the time it will take will be twice as long. Contestants does not have the ability to make two consecutive obstacles at max speed.

## Input
```javascript
// Number of floors - Obstacles
4 6
// Obstacles
112 49 96 98 81 50
96 55 108 90 66 73
109 48 93 105 81 74
100 55 90 92 65 68

1 55
98 76 61 94 67 98 9 34 16 78 106 76 61 94 67 98 9 34 16 78 106 76 61 94 67 98 9 34 16 78 106 76 61 94 67 98 9 34 16 78 106 76 61 94 67 98 9 34 16 78 106 76 61 94 67 

// Delimiter
0 0
```

## Approach
As we were asked to solve this with a Dynamic Programming solution I decided to split the problem in two parts, find the shortest path and get the optimal speed. Although the optimal approach would be using a memoizing algorithm. I used a recursive tree to find the best optimal speed for the formula we had to discover.

## Solution
![](https://i.imgur.com/KYMEo37.gif)

## Usage
`$ make && ./program.run < input.txt`

