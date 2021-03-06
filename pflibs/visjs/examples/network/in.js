var options = {
physics: {
barnesHut: {
gravitationalConstant: -36,
centralGravity: 0.005,
springLength: 230,
springConstant: 0.18
},
maxVelocity: 146,
solver: 'forceAtlas2Based',
timestep: 0.35,
stabilization: {
enabled:true,
iterations:2000,
updateInterval:25
}
},
interaction:{hover:true},
edges:{smooth: false},
layout:{
randomSeed: undefined
}
};

var nodes = [
{id: 1, label: 'D118', value: 3, color:{background:'#9180ff'}},
{id: 2, label: 'D123', value: 5, color:{background:'#7fffa1'}},
{id: 3, label: 'D270', value: 4, color:{background:'#7fffa1'}},
{id: 4, label: 'E222', value: 4, color:{background:'#7fffa1'}},
{id: 5, label: 'F225', value: 1, color:{background:'#9180ff'}},
{id: 6, label: 'F268', value: 1, color:{background:'#9180ff'}},
{id: 7, label: 'G201', value: 2, color:{background:'#fffbbf'}},
{id: 8, label: 'G294', value: 3, color:{background:'#7fffa1'}},
{id: 9, label: 'G329', value: 4, color:{background:'#9180ff'}},
{id: 10, label: 'H313', value: 5, color:{background:'#9180ff'}},
{id: 11, label: 'H35', value: 4, color:{background:'#9180ff'}},
{id: 12, label: 'L129', value: 5, color:{background:'#7fffa1'}},
{id: 13, label: 'L223', value: 2, color:{background:'#9180ff'}},
{id: 14, label: 'L269', value: 5, color:{background:'#7fffa1'}},
{id: 15, label: 'L316', value: 3, color:{background:'#9180ff'}},
{id: 16, label: 'L317', value: 2, color:{background:'#9180ff'}},
{id: 17, label: 'L319', value: 1, color:{background:'#ff80b3'}},
{id: 18, label: 'P127', value: 6, color:{background:'#7fffa1'}},
{id: 19, label: 'P266', value: 1, color:{background:'#7fffa1'}},
{id: 20, label: 'P270', value: 1, color:{background:'#ff80b3'}},
{id: 21, label: 'P315', value: 5, color:{background:'#9180ff'}},
{id: 22, label: 'R120', value: 4, color:{background:'#9180ff'}},
{id: 23, label: 'R292', value: 5, color:{background:'#7fffa1'}},
{id: 24, label: 'R328', value: 6, color:{background:'#9180ff'}},
{id: 25, label: 'S320', value: 2, color:{background:'#fffbbf'}},
{id: 26, label: 'S325', value: 1, color:{background:'#9180ff'}},
{id: 27, label: 'T34', value: 3, color:{background:'#9180ff'}},
{id: 28, label: 'V314', value: 5, color:{background:'#9180ff'}},
{id: 29, label: 'Y221', value: 2, color:{background:'#fffbbf'}},
{id: 30, label: 'Y327', value: 5, color:{background:'#9180ff'}}];

var edges = [
{from: 0, to: 0, color:{color:'red'}, title: -7, value: -7},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: -9},
{from: 0, to: 0, color:{color:'red'}, title: -14, value: -14},
{from: 0, to: 0, color:{color:'red'}, title: -13, value: -13},
{from: 0, to: 2, color:{color:'red'}, title: -27, value: -27},
{from: 0, to: 18, color:{color:'red'}, title: -27, value: -27},
{from: 0, to: 12, color:{color:'red'}, title: -27, value: -27},
{from: 0, to: 0, color:{color:'red'}, title: -15, value: -15},
{from: 0, to: 4, color:{color:'red'}, title: -21, value: -21},
{from: 0, to: 0, color:{color:'red'}, title: -13, value: -13},
{from: 0, to: 0, color:{color:'red'}, title: -11, value: -11},
{from: 0, to: 0, color:{color:'red'}, title: -12, value: -12},
{from: 0, to: 19, color:{color:'red'}, title: -36, value: -36},
{from: 0, to: 14, color:{color:'red'}, title: -43, value: -43},
{from: 0, to: 3, color:{color:'red'}, title: -33, value: 33},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -29, value: 29},
{from: 0, to: 23, color:{color:'red'}, title: -16, value: 16},
{from: 0, to: 8, color:{color:'red'}, title: -43, value: 43},
{from: 0, to: 0, color:{color:'red'}, title: -11, value: 11},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 2, color:{color:'red'}, title: -10, value: 10},
{from: 0, to: 18, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 12, color:{color:'red'}, title: -17, value: 17},
{from: 0, to: 0, color:{color:'red'}, title: -13, value: 13},
{from: 0, to: 4, color:{color:'red'}, title: -12, value: 12},
{from: 0, to: 23, color:{color:'red'}, title: -17, value: 17},
{from: 27, to: 13, color:{color:'green'}, title: 17, value: 17},
{from: 27, to: 28, color:{color:'green'}, title: 13, value: 13},
{from: 27, to: 26, color:{color:'green'}, title: 8, value: 8},
{from: 11, to: 22, color:{color:'green'}, title: 7, value: 7},
{from: 11, to: 10, color:{color:'green'}, title: 8, value: 8},
{from: 11, to: 21, color:{color:'green'}, title: 6, value: 6},
{from: 11, to: 24, color:{color:'green'}, title: 5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 2, color:{color:'red'}, title: -11, value: 11},
{from: 0, to: 18, color:{color:'red'}, title: -11, value: 11},
{from: 0, to: 12, color:{color:'red'}, title: -12, value: 12},
{from: 0, to: 0, color:{color:'red'}, title: -10, value: 10},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 4, color:{color:'red'}, title: -12, value: 12},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 19, color:{color:'red'}, title: -10, value: 10},
{from: 0, to: 14, color:{color:'red'}, title: -14, value: 14},
{from: 0, to: 3, color:{color:'red'}, title: -15, value: 15},
{from: 0, to: 0, color:{color:'red'}, title: -13, value: 13},
{from: 0, to: 23, color:{color:'red'}, title: -10, value: 10},
{from: 0, to: 8, color:{color:'red'}, title: -12, value: 12},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 0, color:{color:'red'}, title: -14, value: 14},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -16, value: 16},
{from: 0, to: 0, color:{color:'red'}, title: -15, value: 15},
{from: 0, to: 0, color:{color:'red'}, title: -10, value: 10},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -15, value: 15},
{from: 0, to: 0, color:{color:'red'}, title: -11, value: 11},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 2, color:{color:'red'}, title: -18, value: 18},
{from: 0, to: 23, color:{color:'red'}, title: -20, value: 20},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -17, value: 17},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 0, color:{color:'red'}, title: -13, value: 13},
{from: 0, to: 0, color:{color:'red'}, title: -18, value: 18},
{from: 0, to: 0, color:{color:'red'}, title: -14, value: 14},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 0, color:{color:'red'}, title: -24, value: 24},
{from: 0, to: 0, color:{color:'red'}, title: -12, value: 12},
{from: 0, to: 0, color:{color:'red'}, title: -15, value: 15},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -14, value: 14},
{from: 0, to: 0, color:{color:'red'}, title: -12, value: 12},
{from: 0, to: 0, color:{color:'red'}, title: -16, value: 16},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 0, color:{color:'red'}, title: -12, value: 12},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -11, value: 11},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 0, color:{color:'red'}, title: -14, value: 14},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -14, value: 14},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 0, color:{color:'red'}, title: -11, value: 11},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 0, color:{color:'red'}, title: -14, value: 14},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 0, color:{color:'red'}, title: -12, value: 12},
{from: 0, to: 0, color:{color:'red'}, title: -18, value: 18},
{from: 0, to: 2, color:{color:'red'}, title: -42, value: 42},
{from: 0, to: 18, color:{color:'red'}, title: -45, value: 45},
{from: 0, to: 12, color:{color:'red'}, title: -46, value: 46},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 4, color:{color:'red'}, title: -52, value: 52},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 0, color:{color:'red'}, title: -16, value: 16},
{from: 0, to: 0, color:{color:'red'}, title: -11, value: 11},
{from: 0, to: 19, color:{color:'red'}, title: -41, value: 41},
{from: 0, to: 14, color:{color:'red'}, title: -54, value: 54},
{from: 0, to: 3, color:{color:'red'}, title: -50, value: 50},
{from: 0, to: 0, color:{color:'red'}, title: -10, value: 10},
{from: 0, to: 23, color:{color:'red'}, title: -50, value: 50},
{from: 0, to: 8, color:{color:'red'}, title: -49, value: 49},
{from: 0, to: 0, color:{color:'red'}, title: -11, value: 11},
{from: 0, to: 0, color:{color:'red'}, title: -15, value: 15},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 2, color:{color:'red'}, title: -31, value: 31},
{from: 0, to: 18, color:{color:'red'}, title: -31, value: 31},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 12, color:{color:'red'}, title: -37, value: 37},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 4, color:{color:'red'}, title: -27, value: 27},
{from: 0, to: 19, color:{color:'red'}, title: -15, value: 15},
{from: 0, to: 14, color:{color:'red'}, title: -15, value: 15},
{from: 0, to: 3, color:{color:'red'}, title: -16, value: 16},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 23, color:{color:'red'}, title: -25, value: 25},
{from: 0, to: 8, color:{color:'red'}, title: -17, value: 17},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 2, color:{color:'red'}, title: -65, value: 65},
{from: 0, to: 18, color:{color:'red'}, title: -70, value: 70},
{from: 0, to: 12, color:{color:'red'}, title: -55, value: 55},
{from: 0, to: 0, color:{color:'red'}, title: -19, value: 19},
{from: 0, to: 0, color:{color:'red'}, title: -19, value: 19},
{from: 0, to: 4, color:{color:'red'}, title: -51, value: 51},
{from: 0, to: 0, color:{color:'red'}, title: -10, value: 10},
{from: 0, to: 0, color:{color:'red'}, title: -18, value: 18},
{from: 0, to: 19, color:{color:'red'}, title: -30, value: 30},
{from: 0, to: 14, color:{color:'red'}, title: -48, value: 48},
{from: 0, to: 3, color:{color:'red'}, title: -39, value: 39},
{from: 0, to: 0, color:{color:'red'}, title: -32, value: 32},
{from: 0, to: 23, color:{color:'red'}, title: -49, value: 49},
{from: 0, to: 8, color:{color:'red'}, title: -40, value: 40},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 0, color:{color:'red'}, title: -15, value: 15},
{from: 1, to: 28, color:{color:'green'}, title: 7, value: 7},
{from: 1, to: 15, color:{color:'green'}, title: 8, value: 8},
{from: 1, to: 16, color:{color:'green'}, title: 8, value: 8},
{from: 22, to: 28, color:{color:'green'}, title: 5, value: 5},
{from: 22, to: 30, color:{color:'green'}, title: 9, value: 9},
{from: 22, to: 24, color:{color:'green'}, title: 5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 2, color:{color:'red'}, title: -28, value: 28},
{from: 0, to: 18, color:{color:'red'}, title: -28, value: 28},
{from: 0, to: 12, color:{color:'red'}, title: -24, value: 24},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 4, color:{color:'red'}, title: -25, value: 25},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 0, color:{color:'red'}, title: -12, value: 12},
{from: 0, to: 19, color:{color:'red'}, title: -26, value: 26},
{from: 0, to: 14, color:{color:'red'}, title: -32, value: 32},
{from: 0, to: 3, color:{color:'red'}, title: -29, value: 29},
{from: 0, to: 23, color:{color:'red'}, title: -26, value: 26},
{from: 0, to: 8, color:{color:'red'}, title: -28, value: 28},
{from: 0, to: 0, color:{color:'red'}, title: -14, value: 14},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 0, color:{color:'red'}, title: -10, value: 10},
{from: 0, to: 2, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 18, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 12, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 4, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 19, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 14, color:{color:'red'}, title: -11, value: 11},
{from: 0, to: 3, color:{color:'red'}, title: -11, value: 11},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 8, color:{color:'red'}, title: -11, value: 11},
{from: 2, to: 0, color:{color:'red'}, title: -54, value: 54},
{from: 2, to: 18, color:{color:'green'}, title: 106, value: 106},
{from: 2, to: 12, color:{color:'green'}, title: 91, value: 91},
{from: 2, to: 0, color:{color:'red'}, title: -42, value: 42},
{from: 2, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 2, to: 4, color:{color:'green'}, title: 84, value: 84},
{from: 2, to: 0, color:{color:'red'}, title: -24, value: 24},
{from: 2, to: 0, color:{color:'red'}, title: -24, value: 24},
{from: 2, to: 0, color:{color:'red'}, title: -18, value: 18},
{from: 2, to: 0, color:{color:'red'}, title: -58, value: 58},
{from: 2, to: 0, color:{color:'red'}, title: -20, value: 20},
{from: 2, to: 0, color:{color:'red'}, title: -31, value: 31},
{from: 2, to: 14, color:{color:'green'}, title: 83, value: 83},
{from: 2, to: 0, color:{color:'red'}, title: -42, value: 42},
{from: 2, to: 20, color:{color:'red'}, title: -97, value: -97},
{from: 2, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 2, to: 0, color:{color:'red'}, title: -30, value: 30},
{from: 2, to: 0, color:{color:'red'}, title: -16, value: 16},
{from: 2, to: 23, color:{color:'green'}, title: 89, value: 89},
{from: 2, to: 0, color:{color:'red'}, title: -28, value: 28},
{from: 2, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 2, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 2, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 12, color:{color:'red'}, title: -59, value: 59},
{from: 0, to: 0, color:{color:'red'}, title: -16, value: 16},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 4, color:{color:'red'}, title: -54, value: 54},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 19, color:{color:'red'}, title: -20, value: 20},
{from: 0, to: 14, color:{color:'red'}, title: -33, value: 33},
{from: 0, to: 3, color:{color:'red'}, title: -29, value: 29},
{from: 0, to: 0, color:{color:'red'}, title: -10, value: 10},
{from: 0, to: 23, color:{color:'red'}, title: -59, value: 59},
{from: 0, to: 8, color:{color:'red'}, title: -25, value: 25},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 18, to: 12, color:{color:'green'}, title: 100, value: 100},
{from: 18, to: 0, color:{color:'red'}, title: -51, value: 51},
{from: 18, to: 4, color:{color:'green'}, title: 94, value: 94},
{from: 18, to: 0, color:{color:'red'}, title: -34, value: 34},
{from: 18, to: 0, color:{color:'red'}, title: -22, value: 22},
{from: 18, to: 0, color:{color:'red'}, title: -19, value: 19},
{from: 18, to: 0, color:{color:'red'}, title: -71, value: 71},
{from: 18, to: 0, color:{color:'red'}, title: -19, value: 19},
{from: 18, to: 0, color:{color:'red'}, title: -32, value: 32},
{from: 18, to: 14, color:{color:'green'}, title: 88, value: 88},
{from: 18, to: 0, color:{color:'red'}, title: -50, value: 50},
{from: 18, to: 3, color:{color:'green'}, title: 76, value: 76},
{from: 18, to: 20, color:{color:'red'}, title: -109, value: -109},
{from: 18, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 18, to: 0, color:{color:'red'}, title: -32, value: 32},
{from: 18, to: 0, color:{color:'red'}, title: -17, value: 17},
{from: 18, to: 23, color:{color:'green'}, title: 90, value: 90},
{from: 18, to: 0, color:{color:'red'}, title: -34, value: 34},
{from: 18, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 18, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 18, to: 0, color:{color:'red'}, title: -12, value: 12},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 0, color:{color:'red'}, title: -14, value: 14},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 0, color:{color:'red'}, title: -12, value: 12},
{from: 12, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 12, to: 4, color:{color:'green'}, title: 84, value: 84},
{from: 12, to: 0, color:{color:'red'}, title: -30, value: 30},
{from: 12, to: 0, color:{color:'red'}, title: -24, value: 24},
{from: 12, to: 0, color:{color:'red'}, title: -21, value: 21},
{from: 12, to: 0, color:{color:'red'}, title: -56, value: 56},
{from: 12, to: 0, color:{color:'red'}, title: -20, value: 20},
{from: 12, to: 0, color:{color:'red'}, title: -22, value: 22},
{from: 12, to: 0, color:{color:'red'}, title: -49, value: 49},
{from: 12, to: 3, color:{color:'green'}, title: 74, value: 74},
{from: 12, to: 20, color:{color:'red'}, title: -94, value: -94},
{from: 12, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 12, to: 0, color:{color:'red'}, title: -29, value: 29},
{from: 12, to: 0, color:{color:'red'}, title: -16, value: 16},
{from: 12, to: 23, color:{color:'green'}, title: 82, value: 82},
{from: 12, to: 0, color:{color:'red'}, title: -32, value: 32},
{from: 12, to: 0, color:{color:'red'}, title: -18, value: 18},
{from: 12, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 12, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 0, color:{color:'red'}, title: -18, value: 18},
{from: 0, to: 4, color:{color:'red'}, title: -45, value: 45},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 0, color:{color:'red'}, title: -16, value: 16},
{from: 0, to: 19, color:{color:'red'}, title: -39, value: 39},
{from: 0, to: 14, color:{color:'red'}, title: -48, value: 48},
{from: 0, to: 3, color:{color:'red'}, title: -43, value: 43},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 23, color:{color:'red'}, title: -43, value: 43},
{from: 0, to: 8, color:{color:'red'}, title: -40, value: 40},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -12, value: 12},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 0, color:{color:'red'}, title: -15, value: 15},
{from: 0, to: 0, color:{color:'red'}, title: -12, value: 12},
{from: 0, to: 20, color:{color:'red'}, title: -23, value: 23},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -11, value: 11},
{from: 0, to: 0, color:{color:'red'}, title: -13, value: 13},
{from: 0, to: 0, color:{color:'red'}, title: -13, value: 13},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 0, color:{color:'red'}, title: -16, value: 16},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 20, color:{color:'red'}, title: -22, value: 22},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -15, value: 15},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 4, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 23, color:{color:'red'}, title: -11, value: 11},
{from: 7, to: 29, color:{color:'green'}, title: 14, value: 14},
{from: 7, to: 25, color:{color:'green'}, title: 5, value: 5},
{from: 29, to: 25, color:{color:'green'}, title: 5, value: 5},
{from: 4, to: 0, color:{color:'red'}, title: -24, value: 24},
{from: 4, to: 0, color:{color:'red'}, title: -66, value: 66},
{from: 4, to: 0, color:{color:'red'}, title: -19, value: 19},
{from: 4, to: 0, color:{color:'red'}, title: -29, value: 29},
{from: 4, to: 0, color:{color:'red'}, title: -49, value: 49},
{from: 4, to: 20, color:{color:'red'}, title: -109, value: -109},
{from: 4, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 4, to: 0, color:{color:'red'}, title: -36, value: 36},
{from: 4, to: 0, color:{color:'red'}, title: -16, value: 16},
{from: 4, to: 23, color:{color:'green'}, title: 121, value: 121},
{from: 4, to: 0, color:{color:'red'}, title: -35, value: 35},
{from: 4, to: 0, color:{color:'red'}, title: -12, value: 12},
{from: 4, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 4, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 0, color:{color:'red'}, title: -10, value: 10},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 0, color:{color:'red'}, title: -10, value: 10},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 19, color:{color:'red'}, title: -32, value: 32},
{from: 0, to: 14, color:{color:'red'}, title: -38, value: 38},
{from: 0, to: 3, color:{color:'red'}, title: -35, value: 35},
{from: 0, to: 0, color:{color:'red'}, title: -13, value: 13},
{from: 0, to: 0, color:{color:'red'}, title: -14, value: 14},
{from: 0, to: 23, color:{color:'red'}, title: -36, value: 36},
{from: 0, to: 8, color:{color:'red'}, title: -34, value: 34},
{from: 0, to: 0, color:{color:'red'}, title: -10, value: 10},
{from: 0, to: 0, color:{color:'red'}, title: -11, value: 11},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 14, color:{color:'red'}, title: -13, value: 13},
{from: 0, to: 3, color:{color:'red'}, title: -11, value: 11},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -16, value: 16},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 23, color:{color:'red'}, title: -63, value: 63},
{from: 0, to: 8, color:{color:'red'}, title: -8, value: 8},
{from: 13, to: 28, color:{color:'green'}, title: 17, value: 17},
{from: 0, to: 0, color:{color:'red'}, title: -11, value: 11},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -15, value: 15},
{from: 5, to: 15, color:{color:'green'}, title: 8, value: 8},
{from: 0, to: 0, color:{color:'red'}, title: -27, value: 27},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 19, color:{color:'red'}, title: -13, value: 13},
{from: 0, to: 14, color:{color:'red'}, title: -17, value: 17},
{from: 0, to: 3, color:{color:'red'}, title: -23, value: 23},
{from: 0, to: 0, color:{color:'red'}, title: -28, value: 28},
{from: 0, to: 23, color:{color:'red'}, title: -22, value: 22},
{from: 0, to: 8, color:{color:'red'}, title: -14, value: 14},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 0, color:{color:'red'}, title: -13, value: 13},
{from: 0, to: 0, color:{color:'red'}, title: -25, value: 25},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 19, color:{color:'red'}, title: -64, value: 64},
{from: 0, to: 14, color:{color:'red'}, title: -81, value: 81},
{from: 0, to: 3, color:{color:'red'}, title: -67, value: 67},
{from: 0, to: 0, color:{color:'red'}, title: -27, value: 27},
{from: 0, to: 23, color:{color:'red'}, title: -57, value: 57},
{from: 0, to: 8, color:{color:'red'}, title: -63, value: 63},
{from: 0, to: 0, color:{color:'red'}, title: -16, value: 16},
{from: 0, to: 0, color:{color:'red'}, title: -28, value: 28},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 0, color:{color:'red'}, title: -11, value: 11},
{from: 0, to: 0, color:{color:'red'}, title: -15, value: 15},
{from: 0, to: 0, color:{color:'red'}, title: -15, value: 15},
{from: 0, to: 20, color:{color:'red'}, title: -39, value: 39},
{from: 0, to: 0, color:{color:'red'}, title: -12, value: 12},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -25, value: 25},
{from: 0, to: 0, color:{color:'red'}, title: -15, value: 15},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 19, color:{color:'red'}, title: -23, value: 23},
{from: 0, to: 14, color:{color:'red'}, title: -26, value: 26},
{from: 0, to: 3, color:{color:'red'}, title: -23, value: 23},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 23, color:{color:'red'}, title: -18, value: 18},
{from: 0, to: 8, color:{color:'red'}, title: -22, value: 22},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -10, value: 10},
{from: 19, to: 0, color:{color:'red'}, title: -29, value: 29},
{from: 19, to: 0, color:{color:'red'}, title: -49, value: 49},
{from: 19, to: 20, color:{color:'red'}, title: -95, value: -95},
{from: 19, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 19, to: 0, color:{color:'red'}, title: -32, value: 32},
{from: 19, to: 0, color:{color:'red'}, title: -24, value: 24},
{from: 19, to: 0, color:{color:'red'}, title: -23, value: 23},
{from: 19, to: 8, color:{color:'green'}, title: 96, value: 96},
{from: 19, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 19, to: 0, color:{color:'red'}, title: -12, value: 12},
{from: 6, to: 28, color:{color:'green'}, title: 8, value: 8},
{from: 0, to: 3, color:{color:'red'}, title: -36, value: 36},
{from: 0, to: 23, color:{color:'red'}, title: -27, value: 27},
{from: 0, to: 8, color:{color:'red'}, title: -36, value: 36},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -15, value: 15},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 14, to: 3, color:{color:'green'}, title: 87, value: 87},
{from: 14, to: 20, color:{color:'red'}, title: -132, value: -132},
{from: 14, to: 0, color:{color:'red'}, title: -10, value: 10},
{from: 14, to: 0, color:{color:'red'}, title: -40, value: 40},
{from: 14, to: 0, color:{color:'red'}, title: -21, value: 21},
{from: 14, to: 23, color:{color:'green'}, title: 80, value: 80},
{from: 14, to: 0, color:{color:'red'}, title: -32, value: 32},
{from: 14, to: 8, color:{color:'green'}, title: 95, value: 95},
{from: 14, to: 0, color:{color:'red'}, title: -12, value: 12},
{from: 14, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 3, color:{color:'red'}, title: -52, value: 52},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -49, value: 49},
{from: 0, to: 23, color:{color:'red'}, title: -50, value: 50},
{from: 0, to: 8, color:{color:'red'}, title: -54, value: 54},
{from: 0, to: 0, color:{color:'red'}, title: -20, value: 20},
{from: 3, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 3, to: 0, color:{color:'red'}, title: -37, value: 37},
{from: 3, to: 0, color:{color:'red'}, title: -24, value: 24},
{from: 3, to: 0, color:{color:'red'}, title: -29, value: 29},
{from: 3, to: 8, color:{color:'green'}, title: 89, value: 89},
{from: 3, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 3, to: 0, color:{color:'red'}, title: -12, value: 12},
{from: 20, to: 0, color:{color:'red'}, title: -54, value: 54},
{from: 20, to: 23, color:{color:'red'}, title: -97, value: -97},
{from: 20, to: 8, color:{color:'red'}, title: -110, value: -110},
{from: 20, to: 0, color:{color:'red'}, title: -23, value: 23},
{from: 20, to: 17, color:{color:'green'}, title: 29, value: 29},
{from: 20, to: 0, color:{color:'red'}, title: -30, value: 30},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 8, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -10, value: 10},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 0, to: 23, color:{color:'red'}, title: -22, value: 22},
{from: 0, to: 8, color:{color:'red'}, title: -36, value: 36},
{from: 0, to: 0, color:{color:'red'}, title: -10, value: 10},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -17, value: 17},
{from: 0, to: 0, color:{color:'red'}, title: -7, value: 7},
{from: 0, to: 23, color:{color:'red'}, title: -13, value: 13},
{from: 0, to: 8, color:{color:'red'}, title: -27, value: 27},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 0, color:{color:'red'}, title: -6, value: 6},
{from: 23, to: 0, color:{color:'red'}, title: -11, value: 11},
{from: 23, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 23, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 0, to: 8, color:{color:'red'}, title: -27, value: 27},
{from: 0, to: 0, color:{color:'red'}, title: -9, value: 9},
{from: 0, to: 0, color:{color:'red'}, title: -5, value: 5},
{from: 0, to: 0, color:{color:'red'}, title: -11, value: 11},
{from: 8, to: 0, color:{color:'red'}, title: -15, value: 15},
{from: 8, to: 0, color:{color:'red'}, title: -13, value: 13},
{from: 0, to: 0, color:{color:'red'}, title: -14, value: 14},
{from: 10, to: 21, color:{color:'green'}, title: 8, value: 8},
{from: 10, to: 30, color:{color:'green'}, title: 6, value: 6},
{from: 10, to: 24, color:{color:'green'}, title: 9, value: 9},
{from: 10, to: 9, color:{color:'green'}, title: 6, value: 6},
{from: 21, to: 30, color:{color:'green'}, title: 5, value: 5},
{from: 21, to: 24, color:{color:'green'}, title: 7, value: 7},
{from: 21, to: 9, color:{color:'green'}, title: 6, value: 6},
{from: 15, to: 16, color:{color:'green'}, title: 8, value: 8},
{from: 0, to: 0, color:{color:'red'}, title: -8, value: 8},
{from: 30, to: 24, color:{color:'green'}, title: 7, value: 7},
{from: 30, to: 9, color:{color:'green'}, title: 10, value: 10},
{from: 24, to: 9, color:{color:'green'}, title: 9, value: 9},
];
