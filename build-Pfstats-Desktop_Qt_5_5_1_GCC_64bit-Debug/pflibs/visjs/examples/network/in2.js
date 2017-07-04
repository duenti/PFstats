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
{id: 1, label: 'A1386', color:{background:'#ffffff'}},
{id: 2, label: 'A841', color:{background:'#ffffff'}},
{id: 3, label: 'A867', color:{background:'#ffffff'}},
{id: 4, label: 'A885', color:{background:'#ffffff'}},
{id: 5, label: 'A971', color:{background:'#ffffff'}},
{id: 6, label: 'Comm2', color:{background:'#7fffa1'}},
{id: 7, label: 'Comm3', color:{background:'#7fffa1'}},
{id: 8, label: 'Comm4', color:{background:'#7fffa1'}},
{id: 9, label: 'Comm5', color:{background:'#7fffa1'}},
{id: 10, label: 'Comm6', color:{background:'#7fffa1'}},
{id: 11, label: 'Comm7', color:{background:'#7fffa1'}},
{id: 12, label: 'G162', color:{background:'#ffffff'}},
{id: 13, label: 'G833', color:{background:'#ffffff'}},
{id: 14, label: 'H842', color:{background:'#ffffff'}},
{id: 15, label: 'K1321', color:{background:'#ffffff'}},
{id: 16, label: 'L1201', color:{background:'#ffffff'}},
{id: 17, label: 'L1526', color:{background:'#ffffff'}},
{id: 18, label: 'L892', color:{background:'#ffffff'}},
{id: 19, label: 'L904', color:{background:'#ffffff'}},
{id: 20, label: 'L909', color:{background:'#ffffff'}},
{id: 21, label: 'N1340', color:{background:'#ffffff'}},
{id: 22, label: 'P1096', color:{background:'#ffffff'}},
{id: 23, label: 'Q1528', color:{background:'#ffffff'}},
{id: 24, label: 'T919', color:{background:'#ffffff'}},
{id: 25, label: 'V1301', color:{background:'#ffffff'}},
{id: 26, label: 'V838', color:{background:'#ffffff'}}];

var edges = [
{from: 6, to: 24, color:{color:'red'}, title: -115},
{from: 7, to: 21, color:{color:'red'}, title: -267},
{from: 7, to: 22, color:{color:'red'}, title: -197},
{from: 7, to: 19, color:{color:'red'}, title: -62},
{from: 7, to: 20, color:{color:'red'}, title: -87},
{from: 7, to: 24, color:{color:'red'}, title: -66},
{from: 7, to: 26, color:{color:'red'}, title: -429},
{from: 7, to: 2, color:{color:'red'}, title: -274},
{from: 7, to: 4, color:{color:'red'}, title: -316},
{from: 7, to: 14, color:{color:'red'}, title: -478},
{from: 8, to: 12, color:{color:'red'}, title: -124},
{from: 9, to: 17, color:{color:'red'}, title: -100},
{from: 9, to: 19, color:{color:'red'}, title: -239},
{from: 9, to: 24, color:{color:'red'}, title: -207},
{from: 9, to: 5, color:{color:'red'}, title: -113},
{from: 10, to: 17, color:{color:'red'}, title: -217},
{from: 10, to: 18, color:{color:'red'}, title: -53},
{from: 10, to: 19, color:{color:'red'}, title: -191},
{from: 10, to: 20, color:{color:'red'}, title: -76},
{from: 10, to: 24, color:{color:'red'}, title: -188},
{from: 10, to: 25, color:{color:'red'}, title: -171},
{from: 10, to: 5, color:{color:'red'}, title: -74},
{from: 10, to: 1, color:{color:'red'}, title: -54},
{from: 10, to: 15, color:{color:'red'}, title: -167},
{from: 10, to: 16, color:{color:'red'}, title: -133},
{from: 10, to: 13, color:{color:'red'}, title: -266},
{from: 11, to: 17, color:{color:'red'}, title: -132},
{from: 11, to: 18, color:{color:'red'}, title: -151},
{from: 11, to: 19, color:{color:'red'}, title: -213},
{from: 11, to: 24, color:{color:'red'}, title: -279},
{from: 11, to: 25, color:{color:'red'}, title: -56},
{from: 11, to: 23, color:{color:'red'}, title: -140},
{from: 11, to: 5, color:{color:'red'}, title: -213},
{from: 11, to: 1, color:{color:'red'}, title: -232},
{from: 11, to: 3, color:{color:'red'}, title: -81},
];
