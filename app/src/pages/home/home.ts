import { Component } from '@angular/core';
import { NavController, Loading, LoadingController } from 'ionic-angular';
import { ArduinoService } from '../../services/arduino.service';
import 'rxjs/add/operator/debounceTime';
import 'rxjs/add/operator/distinctUntilChanged';
import { Observable } from "rxjs/Observable";

@Component({
  selector: 'page-home',
  templateUrl: 'home.html'
})
export class HomePage {
	private power : boolean;
	private brightness : number;
	private speed: number;
	private contrast: number;
	private pattern: number;
	private loader: Loading;

	constructor( public navCtrl: NavController, private arduino: ArduinoService, public loadingController: LoadingController ) { }

	onPowerChange( power : boolean ) {
		this.arduino
			.setPower( power )
			.subscribe( ( data ) => {
				console.log( data );
			}, ( ex ) => {
				console.log( ex );
			} );
	}

	onBrightnessChange( brightness : number ) {
		this.arduino
			.setBrightness( brightness )
			.subscribe( ( data ) => {
				console.log(data);
			}, ( ex ) => {
				console.log( ex );
			} );
	}

	onContrastChange( contrast : number ) {
		this.arduino
			.setContrast( contrast )
			.subscribe( ( data ) => {
				console.log(data);
			}, ( ex ) => {
				console.log( ex );
			} );
	}

	onSpeedChange( speed : number ) {
		this.arduino
			.setSpeed( speed )
			.subscribe( ( data ) => {
				console.log(data);
			}, ( ex ) => {
				console.log( ex );
			} );
	}

	onPatternChange( pattern: number ) {
		this.arduino
			.setPattern( pattern )
			.subscribe( ( data ) => {
				console.log(data);
			}, ( ex ) => {
				console.log( ex );
			} );
	}

	getStatus() {
		// This code block had to be moved to ngAfterViewInit() because it simply refused to work properly when
		// it was in ngOnInit(). It would work in ngOnInit() if I called it twice (???);

		this.arduino
			.getStatus()
			.subscribe( ( data ) => {
				this.loader.dismiss();
				this.power = data.result.power;
				this.brightness = data.result.brightness;
				this.speed = data.result.speed;
				this.contrast = data.result.contrast;
				this.pattern = data.result.pattern;

				console.log( data );
			}, ( error ) => {
				console.log(error);
			} );
	}

	ngOnInit() {
		this.loader = this.loadingController.create({
			content: "Finding Miffy..."
		});
		this.loader.present();
		this.getStatus();
	}
}
