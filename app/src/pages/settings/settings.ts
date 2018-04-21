import { Arduino } from '../../providers/arduino/arduino';
import { Config } from '../../providers/config/config';
import { Component } from '@angular/core';
import {
	IonicPage,
	IonicPageModule,
	Alert,
	AlertController,
	ToastController
} from 'ionic-angular';
import { Storage } from '@ionic/storage';

@IonicPage()
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
	private didConnect: boolean;
	private isConnecting: boolean;
	private state: any;
	public isOnline: boolean = false;
	public isOffline: boolean = false;
	public min_contrast: number;
	public max_contrast: number;
	public min_brightness: number;
	public max_brightness: number;
	public min_speed:number;
	public max_speed:number;

	constructor(
		private arduino: Arduino,
		private storage: Storage,
		private toastController: ToastController,
		private alertController: AlertController ) {
	}

	ionViewDidLoad() {
		this.getState();
		this.getStatus();
	}

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

	onBrightnessChange( e ) {
		if (!e) return;

		this.arduino
			.setBrightness( e.value )
			.subscribe( ( data ) => {
				this.showToast( 'Brightness changed!' );
				this.saveState();
			}, ( ex ) => {
				this.brightness = this.state.brightness;
				this.showToast( 'Brightness changed failed!', 'error' );
			} );
	}

	onContrastChange( e ) {
		if (!e) return;

		this.arduino
			.setContrast( e.value )
			.subscribe( ( data ) => {
				this.showToast( 'Contrast changed!' );
				this.saveState();
			}, ( ex ) => {
				this.contrast = this.state.contrast;
				this.showToast( 'Contrast changed failed!', 'error' );
			} );
	}

	onSpeedChange( e ) {
		if (!e) return;

		this.arduino
			.setSpeed( e.value )
			.subscribe( ( data ) => {
				this.showToast( 'Speed changed!' );
				this.saveState();
			}, ( ex ) => {
				this.speed = this.state.speed;
				this.showToast( 'Speed change failed!', 'error' );
			} );
	}

	onPatternChange( pattern: number ) {
		if (!pattern) return;

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
		this.storage.get( 'subdomain' ).then( ( subdomain ) => {
			if ( subdomain ) {
				this.isConnecting = true;
				this.arduino
					.getStatus( subdomain )
					.subscribe( ( data ) => {
						this.power = data.result.power as boolean;
						this.brightness = data.result.brightness.current;
						this.speed = data.result.speed.current;
						this.contrast = data.result.contrast.current;
						this.pattern = data.result.pattern;
						this.min_brightness = data.result.brightness.min;
						this.max_brightness = data.result.brightness.max;
						this.min_speed = data.result.speed.min;
						this.max_speed = data.result.speed.max;
						this.min_contrast = data.result.contrast.min;
						this.max_contrast = data.result.contrast.max;
						this.didConnect = true;
						this.isConnecting = false;
						this.saveState();
					}, ( ex ) => {
						let alert = this.alertController.create({
							title: Config.alert.title,
							message: Config.alert.message,
							buttons: [{
								text: 'Cancel',
								role: 'cancel',
								handler: () => {
									this.isConnecting = false;
									this.didConnect = false;
								}
							}, {
								text: 'Yes',
								handler: () => {
									this.getStatus();
								}
							}]
						});
						alert.present();
					});
			}
		});
	}

	getState() {
		this.storage.get( 'state' ).then( ( state ) => {
			if ( state ) {
				this.state = {
					contrast: state.contrast,
					speed: state.speed,
					power: state.power,
					brightness: state.brightness,
					pattern: state.pattern
				}
			}
		});
	}

	saveState() {
		this.state = {
			contrast: this.contrast || 0,
			speed: this.speed || 0,
			power: this.power || false,
			brightness: this.brightness || 0,
			pattern: this.pattern || -1
		};

		this.storage.set( 'state', this.state );
	}

	showToast( message: string, className: string = 'success' ): void {
		let toast = this.toastController.create({
			message: message,
			duration: 1750,
			cssClass: className,
		});
		toast.present();
	}
}
