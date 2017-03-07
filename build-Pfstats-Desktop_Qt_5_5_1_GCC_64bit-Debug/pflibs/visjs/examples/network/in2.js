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
{id: 1, label: 'A1805', color:{background:'#ffffff'}},
{id: 2, label: 'A2799', color:{background:'#ffffff'}},
{id: 3, label: 'A2944', color:{background:'#ffffff'}},
{id: 4, label: 'Comm2', color:{background:'#7fffa1'}},
{id: 5, label: 'Comm3', color:{background:'#7fffa1'}},
{id: 6, label: 'I1195', color:{background:'#ffffff'}},
{id: 7, label: 'L1379', color:{background:'#ffffff'}},
{id: 8, label: 'L384', color:{background:'#ffffff'}}];

var edges = [
{from: 4, to: 8, color:{color:'red'}, title: -34},
{from: 4, to: 7, color:{color:'red'}, title: -179},
{from: 4, to: 6, color:{color:'red'}, title: -38},
{from: 4, to: 2, color:{color:'red'}, title: -34},
{from: 4, to: 1, color:{color:'red'}, title: -148},
{from: 5, to: 3, color:{color:'red'}, title: -168},
];
