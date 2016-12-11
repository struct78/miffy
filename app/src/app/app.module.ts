import { NgModule, ErrorHandler } from '@angular/core';
import { IonicApp, IonicModule, IonicErrorHandler } from 'ionic-angular';
import { Storage } from '@ionic/storage';
import { Miffy } from './app.component';
import { SettingsPage } from '../pages/settings/settings';
import { HomePage } from '../pages/home/home';
import { ArduinoService } from '../services/arduino.service';

@NgModule({
  declarations: [
    Miffy,
    SettingsPage,
    HomePage
  ],
  imports: [
    IonicModule.forRoot(Miffy)
  ],
  bootstrap: [IonicApp],
  entryComponents: [
    Miffy,
    SettingsPage,
    HomePage
  ],
  providers: [
		Storage,
		ArduinoService,
		{
			provide: ErrorHandler,
			useClass: IonicErrorHandler
		} ]
})
export class AppModule {}
