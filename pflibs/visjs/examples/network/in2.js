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
{id: 1, label: 'Comm1', color:{background:'#7fffa1'}},
{id: 2, label: 'Comm3', color:{background:'#7fffa1'}}];

var edges = [
{from: 1, to: 2, color:{color:'red'}, title: 0},
];
