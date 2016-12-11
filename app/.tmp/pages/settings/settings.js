import { Component } from '@angular/core';
import { NavController } from 'ionic-angular';
export var SettingsPage = (function () {
    function SettingsPage(navCtrl) {
        this.navCtrl = navCtrl;
    }
    SettingsPage.decorators = [
        { type: Component, args: [{
                    selector: 'page-settings',
                    templateUrl: 'settings.html'
                },] },
    ];
    /** @nocollapse */
    SettingsPage.ctorParameters = [
        { type: NavController, },
    ];
    return SettingsPage;
}());
//# sourceMappingURL=settings.js.map