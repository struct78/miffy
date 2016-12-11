import { Component } from '@angular/core';
import { NavController } from 'ionic-angular';
import { ArduinoService } from '../../services/arduino.service';
import 'rxjs/add/operator/debounceTime';
import 'rxjs/add/operator/distinctUntilChanged';

@Component({
  selector: 'page-home',
  templateUrl: 'home.html'
})
export class HomePage {

  constructor( public navCtrl: NavController, private arduino: ArduinoService ) {

  }

	onPan( e ) {
		console.log( e );
	}

	onRelease( e ) {
		console.log( e );
	}

	onBrightnessChange( brightness : number ) {
		this.arduino
			.setBrightness( brightness )
			.subscribe( ( data ) => {
				console.log(data);
			});
	}

	onSpeedChange( speed : number ) {
		this.arduino
			.setSpeed( speed )
			.subscribe( ( data ) => {
				console.log(data);
			});
	}

	ngOnInit() {
		this.arduino.getStatus();
	}
}
