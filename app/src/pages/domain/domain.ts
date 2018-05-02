import { Arduino } from '../../providers/arduino/arduino';
import { Config } from '../../providers/config/config';
import { Component } from '@angular/core';
import { Storage } from '@ionic/storage';
import { IonicPage, NavController, NavParams } from 'ionic-angular';

/**
 * Generated class for the DomainPage page.
 *
 * See https://ionicframework.com/docs/components/#navigation for more info on
 * Ionic pages and navigation.
 */

@IonicPage()
@Component({
  selector: 'page-domain',
  templateUrl: 'domain.html',
})
export class DomainPage {

  public subdomain : string;

  constructor(
		public arduino: Arduino,
		public storage: Storage,
    public navCtrl: NavController) {
  }

  ionViewDidLoad() {
    this.storage.get( 'subdomain' ).then( ( subdomain ) => {
      this.subdomain = subdomain;
    });
  }
}
