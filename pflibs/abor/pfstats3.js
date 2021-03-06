(function($){
  DeadSimpleRenderer = function(canvas){
    var canvas = $(canvas).get(0)
    var ctx = canvas.getContext("2d");
    var particleSystem = null

    var that = {
      //
      // the particle system will call the init function once, right before the
      // first frame is to be drawn. it's a good place to set up the canvas and
      // to pass the canvas size to the particle system
      //
      init:function(system){
        // save a reference to the particle system for use in the .redraw() loop
        particleSystem = system

        // inform the system of the screen dimensions so it can map coords for us.
        // if the canvas is ever resized, screenSize should be called again with
        // the new dimensions
        particleSystem.screenSize(canvas.width, canvas.height) 
        particleSystem.screenPadding(80) // leave an extra 80px of whitespace per side
      },
      
      // 
      // redraw will be called repeatedly during the run whenever the node positions
      // change. the new positions for the nodes can be accessed by looking at the
      // .p attribute of a given node. however the p.x & p.y values are in the coordinates
      // of the particle system rather than the screen. you can either map them to
      // the screen yourself, or use the convenience iterators .eachNode (and .eachEdge)
      // which allow you to step through the actual node objects but also pass an
      // x,y point in the screen's coordinate system
      // 

      redraw:function(){
        ctx.clearRect(0,0, canvas.width, canvas.height)
        
        particleSystem.eachEdge(function(edge, pt1, pt2){
          // edge: {source:Node, target:Node, length:#, data:{}}
          // pt1:  {x:#, y:#}  source position in screen coords
          // pt2:  {x:#, y:#}  target position in screen coords

          //console.log(edge.data.value)
          // draw a line from pt1 to pt2
          if(edge.data.value < 0){
            ctx.strokeStyle = "red"
          }else{
            ctx.strokeStyle = "green"
          }
          ctx.lineWidth = 1
          ctx.beginPath()
          ctx.moveTo(pt1.x, pt1.y)
          ctx.lineTo(pt2.x, pt2.y)
          ctx.stroke()
          ctx.fillStyle = "black";
          ctx.font = 'italic 13px sans-serif';
          ctx.fillText (edge.data.value, (pt1.x + pt2.x) / 2, (pt1.y + pt2.y) / 2);
        })

        particleSystem.eachNode(function(node, pt){
          // node: {mass:#, p:{x,y}, name:"", data:{}}
          // pt:   {x:#, y:#}  node position in screen coords

          //console.log(node.data.alignName)
          // draw a rectangle centered at pt

          var w = 15
          var label = node.data.alignName
          var aa = label[0]
          var color = "blue"

          ctx.fillStyle = color
          ctx.rect(pt.x-w/2, pt.y-w/2, w,w)
          ctx.fill()


          ctx.fillStyle = "black"
          ctx.fillText(label,pt.x-w/2, pt.y-w/2)
            
        })          
      }
    }
    return that
  }


  $(document).ready(function(){
    var sys = arbor.ParticleSystem(1000, 800, 0.25)
    sys.renderer = DeadSimpleRenderer("#viewport")
    var json = "in3.json"

    var data = $.getJSON(json,function(data){
      sys.graft({nodes:data.nodes, edges:data.edges})
    })

    $("#label > span").html(json.replace(/.json$/,"").toUpperCase())

    $("a.another").click( function(){ 
      window.location.reload(); 
      return false 
    })
  })



})(this.jQuery)