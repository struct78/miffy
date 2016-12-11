import { Injectable } from '@angular/core';
import { Http, Response, Headers, RequestOptions, URLSearchParams } from '@angular/http';
import { Subject }    from 'rxjs/Subject';
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
		//this.storage.clear();
		this.saveDefault( 'speed' , 0.01 );
		this.saveDefault( 'pattern' , Patterns.WIPE );
		this.saveDefault( 'on', false );
		this.saveDefault( 'brightness', 128 );
		this.saveDefault( 'api_url', 'http://192.168.0.22/api' );
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
					let headers = new Headers({ 'Content-Type': 'application/x-www-form-urlencoded' });
					let requestOptions = new RequestOptions({ headers: headers });
					let body = new URLSearchParams();
					body.set( options.key || options.operation , options.value );

					return Observable.fromPromise( this.storage.get( 'api_url' ) )
						.flatMap( ( url ) => {
							return this.http.post( url.concat( '/', options.operation ), body, requestOptions )
								.map( ( response:Response ) => {
									this.savePreference( options.key || options.operation, options.value );
									return response.json();
								} )
								.catch( () =>  {
										return Observable.throw( { error: true } );
								});
						});
				}


				// HTTP GET
				if ( options.method === 'GET' ) {
					return Observable.fromPromise( this.storage.get( 'api_url' ) )
						.flatMap( ( url ) => {
							return this.http.get( url.concat( '/', options.operation ) )
								.map( ( response: Response ) => {
									this.saveResponse( response, options );
								})
								.catch( this.getError );
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

	private getError( ex: Response | any ) : Observable<any> {
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
	 * @name setSpeed
	 * @description Sets the speed of the colour cycle. Range 1 - 100. 1 being the slowest.
	 * @param {number} brightness
	 * @return {Subject<any>} client
	**/
	setSpeed( speed: number ) : Observable<any> {
		return this.post( 'speed', speed );
	}

	private get( operation: String, value: any ) : Observable<any> {
		this.client.next({
			method: 'GET',
			operation: operation,
			value: value
		});

		return this.client;
	}

	private post( operation: String, value: any, key?: any ) : Observable<any> {
		this.client.next({
			method: 'POST',
			operation: operation,
			value: value,
			key: key
		});

		return this.client;
	}

	getStatus() {
		console.log(this.storage);
		/*
		return this.db.openDatabase({
			name: "settings.db",
			location: "default"
		}).then(() => {
			return this.database.executeSql("SELECT TOP 1 FROM Settings", []);
		}).then((data) => {
			 return this.http.get( "http://192.168.0.22/api/status" ).map( ( response:Response ) => response.json() ) );
		});*/
	}
		/*

	  this.people = [];
	  if(data.rows.length > 0) {
	      for(var i = 0; i < data.rows.length; i++) {
	          this.people.push({firstname: data.rows.item(i).firstname, lastname: data.rows.item(i).lastname});
	      }
	  }
	}, (error) => {
	  console.log("ERROR: " + JSON.stringify(error));
	});
		return this.http.get( this.url ).map( ( response:Response ) => response.json().products.find( ( product, i ) => product.url == url ) );
	}*/
}
