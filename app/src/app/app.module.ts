import { NgModule, ErrorHandler } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { IonicApp, IonicModule, IonicErrorHandler } from 'ionic-angular';
import { HttpModule } from '@angular/http';
import { Nightlight } from './app.component';
import { SettingsPage } from '../pages/settings/settings';
import { OfflinePage } from '../pages/offline/offline';
import { ArduinoService } from '../services/arduino.service';

@NgModule({
  declarations: [
    Nightlight,
    SettingsPage,
    OfflinePage
  ],
  imports: [
    BrowserModule,
    HttpModule,
    IonicModule.forRoot(Nightlight)
  ],
  bootstrap: [IonicApp],
  entryComponents: [
    Nightlight,
    SettingsPage
  ],
  providers: [
		ArduinoService,
		{
			provide: ErrorHandler,
			useClass: IonicErrorHandler
		} ]
})
export class AppModule {}
