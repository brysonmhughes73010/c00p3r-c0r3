from jnius import autoclass, cast
from android.permissions import request_permissions, Permission
import time

class AndroidBluetoothHID:
    def __init__(self):
        self.BluetoothAdapter = autoclass('android.bluetooth.BluetoothAdapter')
        self.BluetoothDevice = autoclass('android.bluetooth.BluetoothDevice')
        self.BluetoothProfile = autoclass('android.bluetooth.BluetoothProfile')
        self.Context = autoclass('android.content.Context')
        self.adapter = self.BluetoothAdapter.getDefaultAdapter()
        self.hid_profile = None
        self.connected_device = None

    def check_permissions(self):
        """Check and request necessary Bluetooth permissions"""
        permissions = [
            Permission.BLUETOOTH,
            Permission.BLUETOOTH_ADMIN,
            Permission.ACCESS_FINE_LOCATION
        ]
        request_permissions(permissions)

    def enable_bluetooth(self):
        """Enable Bluetooth if not already enabled"""
        if not self.adapter.isEnabled():
            self.adapter.enable()
            while not self.adapter.isEnabled():
                time.sleep(0.1)

    def get_bonded_devices(self):
        """Get list of paired devices"""
        return self.adapter.getBondedDevices().toArray()

    def connect_hid(self, device_address):
        """Connect to HID device"""
        device = self.adapter.getRemoteDevice(device_address)
        proxy = self.adapter.getProfileProxy(
            cast('android.content.Context', self.Context),
            self.HidServiceListener(),
            self.BluetoothProfile.HID
        )
        self.hid_profile = proxy
        self.connected_device = device

    class HidServiceListener(autoclass('android.bluetooth.BluetoothProfile$ServiceListener')):
        def onServiceConnected(self, profile, proxy):
            """Called when HID service is connected"""
            pass

        def onServiceDisconnected(self, profile):
            """Called when HID service is disconnected"""
            pass

    def send_keyboard_report(self, report):
        """Send HID keyboard report"""
        if self.hid_profile and self.connected_device:
            self.hid_profile.sendReport(self.connected_device, report)

    def disconnect(self):
        """Disconnect from HID device"""
        if self.hid_profile:
            self.adapter.closeProfileProxy(self.BluetoothProfile.HID, self.hid_profile)
            self.hid_profile = None
            self.connected_device = None
