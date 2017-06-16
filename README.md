# lemin
The goal is to move all the ants in a maze to the end as quickly as possible while avoiding collisions.

Given a map layout and the number of the ants in a starting room, display the ants' movements to the ending room. (Only one ant is allowed per room, except the start and end room)

Example:

./lem-in < maps/bottleneck-cut.map
5
# Map: Bottleneck-cut
# <layout>
#           [AA]--------_
#      ____/ || \____    \
#     /     /  \     \    |
#   [a0] [a1]  [a2] [a3]  [Q1]
#     \____ \  / ____/    |
#          \ || /         [Q2]
#           [BB]          |
#      ____/ || \____     [Q3]
#     /     /  \     \    |
#   [b0] [b1]  [b2] [b3]  [Q4]
#     \____ \  / ____/    |
#          \ || /        /
#           [CC]--------/
# </layout>
##start
AA 14  3
a0  6  6
a1 11  6
a2 17  6
a3 22  6
BB 14  9
b0  6 12
b1 11 12
b2 17 12
b3 22 12
##end
CC 14 15
Q1 28  6
Q2 28  8
Q3 28 10
Q4 28 12
# links
AA-a0
AA-a1
AA-a2
AA-a3
a0-BB
a1-BB
a2-BB
a3-BB
BB-b0
BB-b1
BB-b2
BB-b3
b0-CC
b1-CC
b2-CC
b3-CC
AA-Q1
Q1-Q2
Q2-Q3
Q3-Q4
Q4-CC

L1-a0 L2-Q1
L1-BB L2-Q2 L3-a0 L4-Q1
L1-b0 L2-Q3 L3-BB L4-Q2 L5-a0
L1-CC L2-Q4 L3-b0 L4-Q3 L5-BB
L2-CC L3-CC L4-Q4 L5-b0
L4-CC L5-CC
