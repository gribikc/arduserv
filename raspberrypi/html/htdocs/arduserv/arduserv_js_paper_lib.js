var k=0;
		var over_y_valid=0;
		var gain=1;
		update_graphics=function(mode,array){
			var children=project.activeLayer.children;
			for (var i=0;i<children.length;i++) {
				children[i].position.x-=5;

				if(children[i].position.x<=400){
					children[i].remove();
				}
			}
			k++;
			//var sonar_data=new Path.Rectangle(new Point(500, (150+Math.sin(k/10)*100)), 5,5);
			//sonar_data.fillColor='#FF0000';

			//var sonar_data2=new Path.Rectangle(new Point(500, (150+Math.sin(k/5)*100)), 5,5);
			//sonar_data2.fillColor='#00FF00';

			//var sonar_data3=new Path.Rectangle(new Point(500, (150+Math.sin(k/15)*100)), 5,5);
			//sonar_data3.fillColor='#0000FF';

			//var sonar_data4=new Path.Rectangle(new Point(500, (150+Math.sin(k/35)*100)), 5,5);
			//sonar_data4.fillColor='#AFAFAF';

			if(mode==1){
				var sonar_data4=new Path.Rectangle(new Point(500, (150-array[1]*gain)), 5,5);
				sonar_data4.fillColor='#AFAFAF';

				if((150+array[1]*gain)>300 || (150+array[1]*gain)<0){
					gain*=0.75;
				}
			}
			if(mode==2){
				for(var i=0;i<array.length;i++){
					if(array[i]=="1"){
						new Path.Rectangle(new Point(500, (295-i*2)), 5,2);
						children[children.length-1].fillColor='#00FF00';
					}
				}
			}
			
			view.draw();
		}