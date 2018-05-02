import { Arduino } from '../providers/arduino/arduino';
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule } from '@angular/common/http';
import { HttpModule } from '@angular/http';
import { IonicApp, IonicModule, IonicErrorHandler } from 'ionic-angular';
import { IonicStorageModule } from '@ionic/storage';
import { NgModule, ErrorHandler } from '@angular/core';
import { Nightlight } from './app.component';

@NgModule({
	declarations: [
		Nightlight
	],
	imports: [
		BrowserModule,
		HttpModule,
		HttpClientModule,
		IonicModule.forRoot(Nightlight),
		IonicStorageModule.forRoot()
	],
	bootstrap: [IonicApp],
	entryComponents: [
		Nightlight
	],
	providers: [
		Arduino,
		{
			provide: ErrorHandler,
			useClass: IonicErrorHandler
		}]
})
export class AppModule { }
