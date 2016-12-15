import { Injectable } from '@angular/core';
import { Http, Response, Headers, RequestOptions, URLSearchParams } from '@angular/http';
import { Subject } from 'rxjs/Subject';
import { Observable } from "rxjs/Observable";
import { SQLite} from 'ionic-native';
import { Storage } from '@ionic/storage';
import 'rxjs/Rx';

export enum Patterns {
		WIPE = 0,
		RADIAL = 1,
		PULSE = 2
};

@Injectable()
export class ArduinoService {
	private client: Subject<any> = new Subject<any>();
	private debounceTime = 500;

	constructor( private http : Http, private storage: Storage ) {
		this.storage.clear();
		this.saveDefault( 'speed' , 0.01 );
		this.saveDefault( 'pattern' , Patterns.WIPE );
		this.saveDefault( 'on', false );
		this.saveDefault( 'brightness', 128 );
		this.saveDefault( 'api_url', 'http://miffylamp.dynu.net/api' );
		this.createFactory();
	}

	/**
	 * @name createFactory
	 * @description
	 * Due to the Arduino and the Webduino only being able to handle less than 3 or 4 requests a second
	 * we create a factory for the HTTP client, which as a subject can cancel previous requests when
	 * new ones are made, and each request is debounced so as not to overload the Arduino.
	**/
	private createFactory() {
		this.client
			.map( ( v ) => { return v; } )
			.debounceTime( this.debounceTime )
			.switchMap( ( options:any ):any => {

				// HTTP POST
				if ( options.method === 'POST' ) {
					let headers = new Headers( { 'Content-Type': 'application/x-www-form-urlencoded' } );
					let requestOptions = new RequestOptions( { headers: headers } );
					let body = new URLSearchParams();
					body.set( options.key || options.operation , options.value );

					return Observable.fromPromise( this.storage.get( 'api_url' ) )
						.flatMap( ( url ) => {
							return this.http.post( url.concat( '/', options.operation ), body, requestOptions )
								.map( ( response:Response ) => {
									if ( options.save ) {
										return this.saveResponse( options.key || options.operation, options.value );
									}
									return response.json();
								} )
								.catch( this.catchError );
						});
				}


				// HTTP GET
				if ( options.method === 'GET' ) {
					return Observable.fromPromise( this.storage.get( 'api_url' ) )
						.flatMap( ( url ) => {
							return this.http.get( url.concat( '/', options.operation ) )
								.map( ( response: Response ) => {
									if ( options.save ) {
										return this.saveResponse( response, options );
									}
									return response.json();
								})
								.catch( this.catchError );
						});
				}
			})
			.share()
			.subscribe();
	}

	private saveResponse( response : Response, options : any ) {
		this.savePreference( options.key || options.operation, options.value );
		return response.json();
	}

	private catchError( ex: Response | any ) : Observable<any> {
			let message: string;

			if ( ex instanceof Response ) {
				const body = ex.json() || '';
				const err = body.error || JSON.stringify(body);
				message = `${ex.status} - ${ex.statusText || ''} ${err}`;
			} else {
				message = ex.message ? ex.message : ex.toString();
			}

			return Observable.throw( message );
	}
	/**
	 * @name savePreference
	 * @description
	 * Adds default properties to the storage object if they don't exist.
	**/
	private savePreference( key: any, val: any ) {
		this.storage.set( key, val );
	}

	/**
	 * @name saveDefault
	 * @description
	 * Adds default properties to the storage object if they don't exist.
	**/
	private saveDefault( key: any, val: any ) {
		this.storage.get( key ).then( ( data ) => {
			if ( !data ) {
				this.storage.set( key, val );
			}
		});
	}

	/**
	 * @name setBrightness
	 * @description Sets the brightness of the LEDS. Range 1 - 100. 100 being the brightest.
	 * @param {number} brightness
	 * @return {Subject<any>} client
	**/
	setBrightness( brightness: number ) : Observable<any> {
		return this.post( 'brightness', brightness );
	}

	/**
	 * @name setContrast
	 * @description Sets the contrast of the LEDS. Range 1 - 10. 10 being high contrast.
	 * @param {number} contrast
	 * @return {Subject<any>} client
	**/
	setContrast( contrast: number ) : Observable<any> {
		return this.post( 'contrast', contrast );
	}

	/**
	 * @name setSpeed
	 * @description Sets the speed of the colour cycle. Range 1 - 100. 1 being the slowest.
	 * @param {number} speed
	 * @return {Subject<any>} client
	**/
	setSpeed( speed: number ) : Observable<any> {
		return this.post( 'speed', speed );
	}

	/**
	 * @name setPower
	 * @description Toggles the power of the lamp. The Arduino is still running, but the LEDs are turned off.
	 * @param {number} power
	 * @return {Subject<any>} client
	**/
	setPower( power: boolean ) : Observable<any> {
		return this.post( 'power', power );
	}


	/**
	 * @name setPattern
	 * @description Toggles the LED algorithm.
	 * @param {number} pattern
	 * @return {Subject<any>} client
	**/
	setPattern( pattern: number ) : Observable<any> {
		return this.post( 'pattern', pattern );
	}

	/**
	 * @name getStatus
	 * @description Gets the status of the lamp
	 * @return {Subject<any>} client
	**/
	getStatus() : Observable<any> {
		return this.get( 'status', false );
	}

	private get( operation: String, save?: boolean ) : Observable<any> {
		this.client.next({
			method: 'GET',
			operation: operation,
			save: save
		});

		return this.client;
	}

	private post( operation: String, value: any, key?: any, save?: boolean ) : Observable<any> {
		this.client.next({
			method: 'POST',
			operation: operation,
			value: value,
			key: key,
			save: save
		});

		return this.client;
	}
}
