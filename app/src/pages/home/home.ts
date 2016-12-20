import { Component } from '@angular/core';
import { NavController, Loading, LoadingController } from 'ionic-angular';
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
	private contrast: number;
	private loader: Loading;

	constructor( public navCtrl: NavController, private arduino: ArduinoService, public loadingController: LoadingController ) {
	}

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

	onContrastChange( contrast : number ) {
		this.arduino
			.setContrast( contrast )
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
		this.loader = this.loadingController.create({
			content: "Loading Lamp..."
		});
		this.loader.present();

		this.arduino
			.getStatus()
			.subscribe( ( data ) => {
				this.loader.dismiss();
				this.power = data.power;
				this.brightness = data.brightness;
				this.speed = data.speed;
				this.contrast = data.contrast;
			});
	}
}
