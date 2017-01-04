import { Component } from '@angular/core';
import { NavController, Loading, LoadingController, ToastController, AlertController } from 'ionic-angular';
import { ArduinoService } from '../../services/arduino.service';

@Component({
  selector: 'page-settings',
  templateUrl: 'settings.html'
})
export class SettingsPage {
	private power : boolean;
	private brightness : number;
	private speed: number;
	private contrast: number;
	private pattern: number;
	private loader: Loading;
	private didLoad: boolean;
	private state: any;
	public isOnline: boolean = false;
	public isOffline: boolean = false;

	constructor(
		private nav: NavController,
		private arduino: ArduinoService,
		private loadingController: LoadingController,
		private toastController: ToastController,
		private alertController: AlertController
	 ) { }

	onPowerChange( power : boolean ) {
		this.arduino
			.setPower( power )
			.subscribe( ( data ) => {
				if ( data.power ) {
					this.showToast( 'Lamp turned on!' );
				}
				else {
					this.showToast( 'Lamp turned off!' );
				}
				this.saveState();
			}, ( ex ) => {
				this.power = this.state.power;
				this.showToast( 'Power change failed!', 'error' );
			} );
	}

	onBrightnessChange( brightness : number ) {
		this.arduino
			.setBrightness( brightness )
			.subscribe( ( data ) => {
				this.showToast( 'Brightness changed!' );
				this.saveState();
			}, ( ex ) => {
				this.brightness = this.state.brightness;
				this.showToast( 'Brightness changed failed!', 'error' );
			} );
	}

	onContrastChange( contrast : number ) {
		this.arduino
			.setContrast( contrast )
			.subscribe( ( data ) => {
				this.showToast( 'Contrast changed!' );
				this.saveState();
			}, ( ex ) => {
				this.contrast = this.state.contrast;
				this.showToast( 'Contrast changed failed!', 'error' );
			} );
	}

	onSpeedChange( speed : number ) {
		this.arduino
			.setSpeed( speed )
			.subscribe( ( data ) => {
				this.showToast( 'Speed changed!' );
				this.saveState();
			}, ( ex ) => {
				this.speed = this.state.speed;
				this.showToast( 'Speed change failed!', 'error' );
			} );
	}

	onPatternChange( pattern: number ) {
		this.arduino
			.setPattern( pattern )
			.subscribe( ( data ) => {
				this.showToast( 'Pattern updated!' );
				this.saveState();
			}, ( ex ) => {
				this.pattern = this.state.pattern;
				this.showToast( 'Pattern change failed!', 'error' );
			} );
	}

	getStatus() {
		// This code block had to be moved to ngAfterViewInit() because it simply refused to work properly when
		// it was in ngOnInit(). It would work in ngOnInit() if I called it twice (???);
		this.isOffline = false;
		this.isOnline = false;

		this.loader = this.loadingController.create({
			content: "Finding Miffy...",
			spinner: "crescent",
			duration: 2500
		});

		this.loader.present();
		this.loader.onDidDismiss( () => {
			if ( !this.didLoad ) {
				let alert = this.alertController.create({
					title: 'Connect failed',
					message: 'Do you want to try again?',
					buttons: [
						{
							text: 'Cancel',
							role: 'cancel',
							handler: () => {
								this.isOffline = true;
							}
						},
						{
							text: 'Yes',
							handler: () => {
								this.getStatus();
							}
						}
					]
				});
				alert.present();
			}
		} );

		this.arduino
			.getStatus()
			.subscribe( ( data ) => {
				this.loader.dismiss();
				this.power = data.result.power as boolean;
				this.brightness = data.result.brightness;
				this.speed = data.result.speed;
				this.contrast = data.result.contrast;
				this.pattern = data.result.pattern;
				this.didLoad = true;
				this.isOnline = true;
				this.saveState();
			}, ( ex ) => {
				this.showToast( ex.message, 'error' );
			} );
	}

	saveState() {
		this.state = {
			contrast: this.contrast || 0,
			speed: this.speed || 0,
			power: this.power || false,
			brightness: this.brightness || 0,
			pattern: this.pattern || -1
		};
	}

	showToast( message: string, className: string = 'success' ): void {
		let toast = this.toastController.create({
			message: message,
			duration: 1750,
			cssClass: className,
		});
		toast.present();
	}

	ngOnInit(): void {
		this.saveState();
		this.getStatus();
	}
}
