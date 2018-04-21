import { Component } from '@angular/core';
import { Platform } from 'ionic-angular';
import { StatusBar, Splashscreen } from 'ionic-native';
import { Storage } from '@ionic/storage';

@Component({
	templateUrl: 'app.html'
})
export class Nightlight {
	rootPage = 'SettingsPage';

	constructor( platform: Platform, private storage: Storage ) {
		platform.ready().then(() => {
			// Okay, so the platform is ready and our plugins are available.
			// Here you can do any higher level native things you might need.
			StatusBar.hide();
			StatusBar.overlaysWebView( false );
			Splashscreen.hide();

			this.storage.ready().then(() => {
				this.storage.get( 'subdomain' ).then( ( subdomain ) => {
					if (!subdomain) {
						this.rootPage = 'SetupPage';
					}
				});
			});
		});
	}
}
