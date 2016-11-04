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
edges:{smooth: false}
};

var nodes = [
{id: 1, label: 'Comm1'},
{id: 2, label: 'Comm2'},
{id: 3, label: 'Comm3'},
{id: 4, label: 'Comm4'},
{id: 5, label: 'Comm5'},
{id: 6, label: 'Comm6'}];

var edges = [
{from: 2, to: 1, color:{color:'green'}, title: 2},
{from: 3, to: 1, color:{color:'green'}, title: 3},
{from: 3, to: 2, color:{color:'green'}, title: 3},
{from: 4, to: 1, color:{color:'green'}, title: 4},
{from: 4, to: 2, color:{color:'green'}, title: 4},
{from: 4, to: 3, color:{color:'red'}, title: 0},
{from: 5, to: 1, color:{color:'green'}, title: 5},
{from: 5, to: 2, color:{color:'green'}, title: 5},
{from: 5, to: 3, color:{color:'red'}, title: 0},
{from: 5, to: 4, color:{color:'green'}, title: 3},
{from: 6, to: 1, color:{color:'green'}, title: 6},
{from: 6, to: 2, color:{color:'green'}, title: 6},
{from: 6, to: 4, color:{color:'green'}, title: 4},
];
