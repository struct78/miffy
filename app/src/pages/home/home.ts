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
	private power : boolean;
	private brightness : number;
	private speed: number;

  constructor( public navCtrl: NavController, private arduino: ArduinoService ) { }

	onPowerChange( power : boolean ) {
		this.arduino
			.setPower( power )
			.subscribe( ( data ) => {
				console.log( data );
			})
			.unsubscribe();
	}

	onBrightnessChange( brightness : number ) {
		this.arduino
			.setBrightness( brightness )
			.subscribe( ( data ) => {
				console.log(data);
			})
			.unsubscribe();
	}

	onSpeedChange( speed : number ) {
		this.arduino
			.setSpeed( speed )
			.subscribe( ( data ) => {
				console.log(data);
			})
			.unsubscribe();
	}

	onPatternChange( pattern: number ) {
		this.arduino
			.setPattern( pattern )
			.subscribe( ( data ) => {
				console.log(data);
			})
			.unsubscribe();
	}

	ngOnInit() {
		this.arduino
			.getStatus()
			.subscribe( ( data ) => {
				console.log( data );
				this.power = data.power;
				this.brightness = data.brightness;
				this.speed = data.speed;
			});
	}
}
