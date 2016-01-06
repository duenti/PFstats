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
          //ctx.fillStyle = "black";
          //ctx.font = 'italic 13px sans-serif';
          //ctx.fillText (edge.data.value, (pt1.x + pt2.x) / 2, (pt1.y + pt2.y) / 2);
        })

        particleSystem.eachNode(function(node, pt){
          // node: {mass:#, p:{x,y}, name:"", data:{}}
          // pt:   {x:#, y:#}  node position in screen coords

          //console.log(node.data.alignName)
          // draw a rectangle centered at pt

          //////COLOURS LEGEND////////
          //ESSENTIAL:
          ////NON-BORDER
          //NOT-ESSENTIAL:
          ////BLACK BORDER
          //
          ////////////////////////////
          //ALIPHATIC:
          //A: Crimson
          //G: DarkRed
          //I: FireBrick
          //L: Maroon
          //P: Red
          //V: Tomato
          //AROMATIC:
          //F: DarkGreen 
          //W: Chartreuse 
          //Y: LawnGreen 
          //ACIDIC:
          //D: Coral
          //E: DarkOrange
          //BASIC:
          //R: Aqua
          //H: DodgerBlue 
          //K: LightSkyBlue 
          //HYDROXYLIC:
          //S: Magenta 
          //T: Orchid 
          //SULFUR-CONTAINING:
          //C: DarkGoldenRod 
          //M: Gold
          //AMIDIC:
          //N: DarkBlue 
          //Q: Indigo
          ////////////////////////////////


          var w = 10
          var label = node.data.alignName
          var aa = label[0]
          var color = "white"

          switch(aa){
            case "A":
              color = "Crimson"
              break
            case "G":
              color = "DarkRed"
              break
            case "I":
              color = "FireBrick"
              break
            case "L":
              color = "Maroon"
              break
            case "P":
              color = "Red"
              break
            case "V":
              color = "Tomato"
              break
            case "F":
              color = "DarkGreen"
              break
            case "W":
              color = "Chartreuse"
              break
            case "Y":
              color = "LawnGreen"
              break
            case "D":
              color = "Coral"
              break
            case "E":
              color = "DarkOrange"
              break
            case "R":
              color = "Aqua"
              break
            case "H":
              color = "DodgerBlue"
              break
            case "K":
              color = "LightSkyBlue"
              break
            case "S":
              color = "Magenta"
              break
            case "T":
              color = "Orchid"
              break
            case "C":
              color = "DarkGoldenRod"
              break
            case "M":
              color = "Gold"
              break
            case "N":
              color = "DarkBlue"
              break
            case "Q":
              color = "Indigo"
              break
          }

          ctx.fillStyle = color
          ctx.fillRect(pt.x-w/2, pt.y-w/2, w,w)
          


          ctx.fillStyle = "black"
          ctx.fillText(label,pt.x-w/2, pt.y-w/2)
          
          if(aa=="A" || aa=="G" || aa=="P" || aa=="Y" || aa=="D" || aa=="E" || aa=="r" || aa=="S" || aa=="C" || aa=="N" || aa=="Q"){
          //If aa is essential
            ctx.lineWidth = 1
            ctx.strokeStyle = "black"
            ctx.strokeRect(pt.x-w/2, pt.y-w/2, w,w)
          }
        })          
      }
    }
    return that
  }


  $(document).ready(function(){
    var sys = arbor.ParticleSystem(1000, 800, 0.25)
    sys.renderer = DeadSimpleRenderer("#viewport")
    var json = "in1.json"

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