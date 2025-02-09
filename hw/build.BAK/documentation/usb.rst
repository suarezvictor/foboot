USB
===

USB Device Tri-FIFO
-------------------

This is a three-FIFO USB device.  It presents one FIFO each for ``IN``, ``OUT``, and
``SETUP`` data.  This allows for up to 16 ``IN`` and 16 ``OUT`` endpoints
without sacrificing many FPGA resources.

USB supports four types of transfers: control, bulk, interrupt, and isochronous.
This device does not yet support isochronous transfers, however it supports the
other types of transfers.


Interrupt and Bulk Transfers
----------------------------

Interrupt and bulk transfers are similar from an implementation standpoint --
they differ only in terms of how often they are transmitted.

These transfers can be made to any endpoint, and may even be interleaved.  However,
due to the nature of ``TriEndpointInterface`` any attempt by the host to interleave
transfers will result in a ``NAK``, and the host will retry later when the buffer
is empty.

IN Transfers
^^^^^^^^^^^^

To make an ``IN`` transfer (i.e. to send data to the host), write the data to
``IN_DATA``.  This is a FIFO, and each write to this endpoint will advance the
FIFO pointer automatically.  This FIFO is 64 bytes deep.  USB ``DATA`` packets
contain a CRC16 checksum, which is automatically added to any ``IN`` transfers.

``TriEndpointInterface`` will continue to respond ``NAK`` until you arm the buffer.
Do this by writing the endpoint number to ``IN_CTRL.EPNO``.  This will tell the device
that it should send the data the next time the host asks for it.

Once the data has been transferred, the device will raise an interrupt and you
can begin re-filling the buffer, or fill it with data for a different endpoint.

To send an empty packet, avoid writing any data to ``IN_DATA`` and simply write
the endpoint number to ``IN_CTRL.EPNO``.

The CRC16 will be automatically appended to the end of the transfer.

OUT Transfers
^^^^^^^^^^^^^

To respond to an ``OUT`` transfer (i.e. to receive data from the host), enable
a particular endpoint by writing to ``OUT_CTRL.EPNO`` with the ``OUT_CTRL.ENABLE``
bit set.  This will tell the device to stop responding ``NAK`` to that particular
endpoint and to accept any incoming data into a 66-byte FIFO, provided the FIFO
is empty.

Once the host sends data, an interrupt will be raised and that particular endpoint's
``ENABLE`` will be set to ``0``.  This prevents any additional data from entering
the FIFO while the device examines the data.

The FIFO will contain two extra bytes, which are the two-byte CRC16 of the packet.
You can safely discard these bytes.  Because of this, a zero-byte transfer will
be two-bytes, and a full 64-byte transfer will be 66 bytes.

To determine which endpoint the ``OUT`` packet was sent to, refer to
``OUT_STATUS.EPNO``.  This field is only updated when a successful packet is received,
and will not change until the ``OUT`` FIFO is re-armed.

The ``OUT`` FIFO will continue to respond to the host with with ``NAK`` until the
``OUT_EV_PENDING.DONE`` bit is cleared.

Additionally, to continue receiving data on that particular endpoint, you will need
to re-enable it by writing the endpoint number, along with the ``OUT_CTRL.ENABLE``
to ``OUT_CTRL``.


Control Transfers
-----------------

Control transfers are complicated, and are the first sort of transfer that
the host uses.  Such transfers have three distinct phases.

The first phase is the ``SETUP`` phase, where the host sends an 8-byte ``SETUP``
packet.  These ``SETUP`` packets must always be acknowledged, so any such packet
from the host will get loaded into the ``SETUP`` FIFO immediately, and an interrupt
event raised.  If, for some reason, the device hasn't drained this ``SETUP``
FIFO from a previous transaction, the FIFO will be cleared automatically.

Once the ``SETUP`` packet is handled, the host will send an ``IN`` or ``OUT``
packet.  If the host sends an ``OUT`` packet, then the ``OUT`` buffer must be
cleared, the ``OUT.DONE`` interrupt handled, and the ``OUT_CTRL.ENABLE`` bit
must be set for the appropriate endpoint, usually EP0.  The device will not
accept any data as long as these three conditions are not met.

If the host sends an ``IN`` packet, the device will respond with ``NAK`` if
no data has queued.  To queue data, fill the ``IN_DATA`` buffer, then write
``0`` to ``IN_CTRL``.

You can continue to fill the buffer (for ``IN`` packets) or drain the buffer
and re-enable the endpoint (for ``OUT`` packets) until the host has finished
the transfer.

When the host has finished, it will send the opposite packet type.  If it
is making ``IN`` transfers, it will send a single ``OUT`` packet, or if it
is making ``OUT`` transfers it will send a single ``IN`` packet.
You must handle this transaction yourself.

Stalling an Endpoint
^^^^^^^^^^^^^^^^^^^^

When the host sends a request that cannot be processed -- for example requesting
a descriptor that does not exist -- the device must respond with ``STALL``.

Each endpoint keeps track of its own ``STALL`` state, though a ``SETUP`` packet
will clear the ``STALL`` state for the specified endpoint (usually EP0).

To set or clear the ``STALL`` bit of an ``IN`` endpoint, write its endpoint number
to ``IN_CTRL.EPNO`` with the ``IN_CTRL.STALL`` bit either set or clear.  If
this bit is set, then the device will respond to the next ``IN`` packet from the
host to that particular endpoint with ``STALL``.  If the bit is clear, then
the next ``IN`` packet will be responded to with ``ACK`` and the contents of
the ``IN`` FIFO.

To stall an ``OUT`` endpoint, write to ``OUT_CTRL.EPNO`` with the ``OUT_CTRL.STALL``
and ``OUT_CTRL.ENABLE`` bits set.  To unstall, write to ``OUT_CTRL.EPNO`` with the
``OUT_CTRL.STALL`` bit and ``OUT_CTRL.ENABLE`` bits cleared.  Note that
``OUT_CTRL.ENABLE`` indicates whether any response sould be sent at all, which is
why it must be set or cleared at the same time.


Register Listing for USB
------------------------

+----------------------------------------------------+------------------------------------------+
| Register                                           | Address                                  |
+====================================================+==========================================+
| :ref:`USB_PULLUP_OUT <USB_PULLUP_OUT>`             | :ref:`0xe0004800 <USB_PULLUP_OUT>`       |
+----------------------------------------------------+------------------------------------------+
| :ref:`USB_ADDRESS <USB_ADDRESS>`                   | :ref:`0xe0004804 <USB_ADDRESS>`          |
+----------------------------------------------------+------------------------------------------+
| :ref:`USB_NEXT_EV <USB_NEXT_EV>`                   | :ref:`0xe0004808 <USB_NEXT_EV>`          |
+----------------------------------------------------+------------------------------------------+
| :ref:`USB_SETUP_DATA <USB_SETUP_DATA>`             | :ref:`0xe000480c <USB_SETUP_DATA>`       |
+----------------------------------------------------+------------------------------------------+
| :ref:`USB_SETUP_CTRL <USB_SETUP_CTRL>`             | :ref:`0xe0004810 <USB_SETUP_CTRL>`       |
+----------------------------------------------------+------------------------------------------+
| :ref:`USB_SETUP_STATUS <USB_SETUP_STATUS>`         | :ref:`0xe0004814 <USB_SETUP_STATUS>`     |
+----------------------------------------------------+------------------------------------------+
| :ref:`USB_SETUP_EV_STATUS <USB_SETUP_EV_STATUS>`   | :ref:`0xe0004818 <USB_SETUP_EV_STATUS>`  |
+----------------------------------------------------+------------------------------------------+
| :ref:`USB_SETUP_EV_PENDING <USB_SETUP_EV_PENDING>` | :ref:`0xe000481c <USB_SETUP_EV_PENDING>` |
+----------------------------------------------------+------------------------------------------+
| :ref:`USB_SETUP_EV_ENABLE <USB_SETUP_EV_ENABLE>`   | :ref:`0xe0004820 <USB_SETUP_EV_ENABLE>`  |
+----------------------------------------------------+------------------------------------------+
| :ref:`USB_IN_DATA <USB_IN_DATA>`                   | :ref:`0xe0004824 <USB_IN_DATA>`          |
+----------------------------------------------------+------------------------------------------+
| :ref:`USB_IN_CTRL <USB_IN_CTRL>`                   | :ref:`0xe0004828 <USB_IN_CTRL>`          |
+----------------------------------------------------+------------------------------------------+
| :ref:`USB_IN_STATUS <USB_IN_STATUS>`               | :ref:`0xe000482c <USB_IN_STATUS>`        |
+----------------------------------------------------+------------------------------------------+
| :ref:`USB_IN_EV_STATUS <USB_IN_EV_STATUS>`         | :ref:`0xe0004830 <USB_IN_EV_STATUS>`     |
+----------------------------------------------------+------------------------------------------+
| :ref:`USB_IN_EV_PENDING <USB_IN_EV_PENDING>`       | :ref:`0xe0004834 <USB_IN_EV_PENDING>`    |
+----------------------------------------------------+------------------------------------------+
| :ref:`USB_IN_EV_ENABLE <USB_IN_EV_ENABLE>`         | :ref:`0xe0004838 <USB_IN_EV_ENABLE>`     |
+----------------------------------------------------+------------------------------------------+
| :ref:`USB_OUT_DATA <USB_OUT_DATA>`                 | :ref:`0xe000483c <USB_OUT_DATA>`         |
+----------------------------------------------------+------------------------------------------+
| :ref:`USB_OUT_CTRL <USB_OUT_CTRL>`                 | :ref:`0xe0004840 <USB_OUT_CTRL>`         |
+----------------------------------------------------+------------------------------------------+
| :ref:`USB_OUT_STATUS <USB_OUT_STATUS>`             | :ref:`0xe0004844 <USB_OUT_STATUS>`       |
+----------------------------------------------------+------------------------------------------+
| :ref:`USB_OUT_EV_STATUS <USB_OUT_EV_STATUS>`       | :ref:`0xe0004848 <USB_OUT_EV_STATUS>`    |
+----------------------------------------------------+------------------------------------------+
| :ref:`USB_OUT_EV_PENDING <USB_OUT_EV_PENDING>`     | :ref:`0xe000484c <USB_OUT_EV_PENDING>`   |
+----------------------------------------------------+------------------------------------------+
| :ref:`USB_OUT_EV_ENABLE <USB_OUT_EV_ENABLE>`       | :ref:`0xe0004850 <USB_OUT_EV_ENABLE>`    |
+----------------------------------------------------+------------------------------------------+

USB_PULLUP_OUT
^^^^^^^^^^^^^^

`Address: 0xe0004800 + 0x0 = 0xe0004800`

    GPIO Output(s) Control.

    .. wavedrom::
        :caption: USB_PULLUP_OUT

        {
            "reg": [
                {"name": "pullup_out", "bits": 1},
                {"bits": 7},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


USB_ADDRESS
^^^^^^^^^^^

`Address: 0xe0004800 + 0x4 = 0xe0004804`

    Sets the USB device address, in order to ignore packets going to other devices
    on the bus. This value is reset when the host issues a USB Device Reset
    condition.

    .. wavedrom::
        :caption: USB_ADDRESS

        {
            "reg": [
                {"name": "addr",  "bits": 7},
                {"bits": 1}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+---------------------------------------------------------+
| Field | Name | Description                                             |
+=======+======+=========================================================+
| [6:0] | ADDR | Write the USB address from USB ``SET_ADDRESS`` packets. |
+-------+------+---------------------------------------------------------+

USB_NEXT_EV
^^^^^^^^^^^

`Address: 0xe0004800 + 0x8 = 0xe0004808`

    In ``eptri``, there are three endpoints.  It is possible for an IRQ to fire and
    have all three bits set.  Under these circumstances it can be difficult to know
    which event to process first.  Use this register to determine which event needs
    to be processed first. Only one bit will ever be set at a time.

    .. wavedrom::
        :caption: USB_NEXT_EV

        {
            "reg": [
                {"name": "in",  "bits": 1},
                {"name": "out",  "bits": 1},
                {"name": "setup",  "bits": 1},
                {"name": "reset",  "bits": 1},
                {"bits": 4}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+-------+-----------------------------------------------+
| Field | Name  | Description                                   |
+=======+=======+===============================================+
| [0]   | IN    | ``1`` if the next event is an ``IN`` event    |
+-------+-------+-----------------------------------------------+
| [1]   | OUT   | ``1`` if the next event is an ``OUT`` event   |
+-------+-------+-----------------------------------------------+
| [2]   | SETUP | ``1`` if the next event is an ``SETUP`` event |
+-------+-------+-----------------------------------------------+
| [3]   | RESET | ``1`` if the next event is a ``RESET`` event  |
+-------+-------+-----------------------------------------------+

USB_SETUP_DATA
^^^^^^^^^^^^^^

`Address: 0xe0004800 + 0xc = 0xe000480c`

    Data from the last ``SETUP`` transactions.  It will be 10 bytes long, because it
    will include the CRC16.  This is a FIFO, and the queue is advanced
    automatically.

    .. wavedrom::
        :caption: USB_SETUP_DATA

        {
            "reg": [
                {"name": "data",  "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+---------------------------------+
| Field | Name | Description                     |
+=======+======+=================================+
| [7:0] | DATA | The next byte of ``SETUP`` data |
+-------+------+---------------------------------+

USB_SETUP_CTRL
^^^^^^^^^^^^^^

`Address: 0xe0004800 + 0x10 = 0xe0004810`

    Controls for managing how to handle ``SETUP`` transactions.

    .. wavedrom::
        :caption: USB_SETUP_CTRL

        {
            "reg": [
                {"bits": 5},
                {"name": "reset",  "type": 4, "bits": 1},
                {"bits": 2}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+-------+--------------------------------------------------+
| Field | Name  | Description                                      |
+=======+=======+==================================================+
| [5]   | RESET | Write a ``1`` here to reset the `SETUP` handler. |
+-------+-------+--------------------------------------------------+

USB_SETUP_STATUS
^^^^^^^^^^^^^^^^

`Address: 0xe0004800 + 0x14 = 0xe0004814`

    Status about the most recent ``SETUP`` transactions, and the state of the FIFO.

    .. wavedrom::
        :caption: USB_SETUP_STATUS

        {
            "reg": [
                {"name": "epno",  "bits": 4},
                {"name": "have",  "bits": 1},
                {"name": "pend",  "bits": 1},
                {"name": "is_in",  "bits": 1},
                {"name": "data",  "bits": 1}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+-------+-----------------------------------------------------------+
| Field | Name  | Description                                               |
+=======+=======+===========================================================+
| [3:0] | EPNO  | The destination endpoint for the most recent SETUP token. |
+-------+-------+-----------------------------------------------------------+
| [4]   | HAVE  | ``1`` if there is data in the FIFO.                       |
+-------+-------+-----------------------------------------------------------+
| [5]   | PEND  | ``1`` if there is an IRQ pending.                         |
+-------+-------+-----------------------------------------------------------+
| [6]   | IS_IN | ``1`` if an IN stage was detected.                        |
+-------+-------+-----------------------------------------------------------+
| [7]   | DATA  | ``1`` if a DATA stage is expected.                        |
+-------+-------+-----------------------------------------------------------+

USB_SETUP_EV_STATUS
^^^^^^^^^^^^^^^^^^^

`Address: 0xe0004800 + 0x18 = 0xe0004818`

    This register contains the current raw level of the Event trigger.  Writes to this register have no effect.

    .. wavedrom::
        :caption: USB_SETUP_EV_STATUS

        {
            "reg": [
                {"name": "ready",  "bits": 1},
                {"name": "reset",  "bits": 1},
                {"bits": 6}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+-------+----------------------------+
| Field | Name  | Description                |
+=======+=======+============================+
| [0]   | READY | Level of the `ready` event |
+-------+-------+----------------------------+
| [1]   | RESET | Level of the `reset` event |
+-------+-------+----------------------------+

USB_SETUP_EV_PENDING
^^^^^^^^^^^^^^^^^^^^

`Address: 0xe0004800 + 0x1c = 0xe000481c`

    When an Event occurs, the corresponding bit will be set in this register.  To clear the Event, set the corresponding bit in this register.

    .. wavedrom::
        :caption: USB_SETUP_EV_PENDING

        {
            "reg": [
                {"name": "ready",  "bits": 1},
                {"name": "reset",  "bits": 1},
                {"bits": 6}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+-------+---------------------------------------------------------------------------------------------------------+
| Field | Name  | Description                                                                                             |
+=======+=======+=========================================================================================================+
| [0]   | READY |                                                                                                         |
|       |       |                                             Indicates a ``SETUP`` packet has arrived                    |
|       |       |                                             and is waiting in the ``SETUP`` FIFO.                       |
+-------+-------+---------------------------------------------------------------------------------------------------------+
| [1]   | RESET |                                                                                                         |
|       |       |                                                         Indicates a USB ``RESET`` condition             |
|       |       |                                                         has occurred, and the ``ADDRESS`` is now ``0``. |
+-------+-------+---------------------------------------------------------------------------------------------------------+

USB_SETUP_EV_ENABLE
^^^^^^^^^^^^^^^^^^^

`Address: 0xe0004800 + 0x20 = 0xe0004820`

    This register enables the corresponding Events.  Write a `0` to this register to disable individual events.

    .. wavedrom::
        :caption: USB_SETUP_EV_ENABLE

        {
            "reg": [
                {"name": "ready",  "bits": 1},
                {"name": "reset",  "bits": 1},
                {"bits": 6}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+-------+-----------------------------------------+
| Field | Name  | Description                             |
+=======+=======+=========================================+
| [0]   | READY | Write a `1` to enable the `ready` Event |
+-------+-------+-----------------------------------------+
| [1]   | RESET | Write a `1` to enable the `reset` Event |
+-------+-------+-----------------------------------------+

USB_IN_DATA
^^^^^^^^^^^

`Address: 0xe0004800 + 0x24 = 0xe0004824`

    Each byte written into this register gets added to an outgoing FIFO. Any bytes
    that are written here will be transmitted in the order in which they were added.
    The FIFO queue is automatically advanced with each write. The FIFO queue is 64
    bytes deep.  If you exceed this amount, the result is undefined.

    .. wavedrom::
        :caption: USB_IN_DATA

        {
            "reg": [
                {"name": "data",  "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+------------------------------------+
| Field | Name | Description                        |
+=======+======+====================================+
| [7:0] | DATA | The next byte to add to the queue. |
+-------+------+------------------------------------+

USB_IN_CTRL
^^^^^^^^^^^

`Address: 0xe0004800 + 0x28 = 0xe0004828`

    Enables transmission of data in response to ``IN`` tokens, or resets the
    contents of the FIFO.

    .. wavedrom::
        :caption: USB_IN_CTRL

        {
            "reg": [
                {"name": "epno",  "bits": 4},
                {"bits": 1},
                {"name": "reset",  "type": 4, "bits": 1},
                {"name": "stall",  "type": 4, "bits": 1},
                {"bits": 1}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+-------+---------------------------------------------------------------------+
| Field | Name  | Description                                                         |
+=======+=======+=====================================================================+
| [3:0] | EPNO  | The endpoint number for the transaction that is queued in the FIFO. |
+-------+-------+---------------------------------------------------------------------+
| [5]   | RESET | Write a ``1`` here to clear the contents of the FIFO.               |
+-------+-------+---------------------------------------------------------------------+
| [6]   | STALL | Write a ``1`` here to stall the EP written in ``EP``.               |
+-------+-------+---------------------------------------------------------------------+

USB_IN_STATUS
^^^^^^^^^^^^^

`Address: 0xe0004800 + 0x2c = 0xe000482c`

    Status about the IN handler.  As soon as you write to `IN_DATA`,
    ``IN_STATUS.HAVE`` should go to ``1``.

    .. wavedrom::
        :caption: USB_IN_STATUS

        {
            "reg": [
                {"name": "idle",  "bits": 1},
                {"bits": 3},
                {"name": "have",  "bits": 1},
                {"name": "pend",  "bits": 1},
                {"bits": 2}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+--------------------------------------------------------------+
| Field | Name | Description                                                  |
+=======+======+==============================================================+
| [0]   | IDLE | This value is ``1`` if the packet has finished transmitting. |
+-------+------+--------------------------------------------------------------+
| [4]   | HAVE | This value is ``0`` if the FIFO is empty.                    |
+-------+------+--------------------------------------------------------------+
| [5]   | PEND | ``1`` if there is an IRQ pending.                            |
+-------+------+--------------------------------------------------------------+

USB_IN_EV_STATUS
^^^^^^^^^^^^^^^^

`Address: 0xe0004800 + 0x30 = 0xe0004830`

    This register contains the current raw level of the Event trigger.  Writes to this register have no effect.

    .. wavedrom::
        :caption: USB_IN_EV_STATUS

        {
            "reg": [
                {"name": "done",  "bits": 1},
                {"bits": 7}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+---------------------------+
| Field | Name | Description               |
+=======+======+===========================+
| [0]   | DONE | Level of the `done` event |
+-------+------+---------------------------+

USB_IN_EV_PENDING
^^^^^^^^^^^^^^^^^

`Address: 0xe0004800 + 0x34 = 0xe0004834`

    When an Event occurs, the corresponding bit will be set in this register.  To clear the Event, set the corresponding bit in this register.

    .. wavedrom::
        :caption: USB_IN_EV_PENDING

        {
            "reg": [
                {"name": "done",  "bits": 1},
                {"bits": 7}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+------------------------------------------------------------------------------------+
| Field | Name | Description                                                                        |
+=======+======+====================================================================================+
| [0]   | DONE |                                                                                    |
|       |      |             Indicates that the host has successfully transferred an ``IN`` packet, |
|       |      |             and that the FIFO is now empty.                                        |
|       |      |                                                                                    |
+-------+------+------------------------------------------------------------------------------------+

USB_IN_EV_ENABLE
^^^^^^^^^^^^^^^^

`Address: 0xe0004800 + 0x38 = 0xe0004838`

    This register enables the corresponding Events.  Write a `0` to this register to disable individual events.

    .. wavedrom::
        :caption: USB_IN_EV_ENABLE

        {
            "reg": [
                {"name": "done",  "bits": 1},
                {"bits": 7}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+----------------------------------------+
| Field | Name | Description                            |
+=======+======+========================================+
| [0]   | DONE | Write a `1` to enable the `done` Event |
+-------+------+----------------------------------------+

USB_OUT_DATA
^^^^^^^^^^^^

`Address: 0xe0004800 + 0x3c = 0xe000483c`

    Data received from the host will go into a FIFO.  This register reflects the
    contents of the top byte in that FIFO.  Reading from this register advances the
    FIFO pointer.

    .. wavedrom::
        :caption: USB_OUT_DATA

        {
            "reg": [
                {"name": "data",  "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+-----------------------------------+
| Field | Name | Description                       |
+=======+======+===================================+
| [7:0] | DATA | The top byte of the receive FIFO. |
+-------+------+-----------------------------------+

USB_OUT_CTRL
^^^^^^^^^^^^

`Address: 0xe0004800 + 0x40 = 0xe0004840`

    Controls for receiving packet data.  To enable an endpoint, write its value to
    ``epno``, with the ``enable`` bit set to ``1`` to enable an endpoint, or ``0``
    to disable it. Resetting the OutHandler will set all ``enable`` bits to 0.

    Similarly, you can adjust the ``STALL`` state by setting or clearing the
    ``stall`` bit.

    .. wavedrom::
        :caption: USB_OUT_CTRL

        {
            "reg": [
                {"name": "epno",  "bits": 4},
                {"name": "enable",  "bits": 1},
                {"name": "reset",  "type": 4, "bits": 1},
                {"name": "stall",  "bits": 1},
                {"bits": 1}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+--------+-----------------------------------------------------------------------+
| Field | Name   | Description                                                           |
+=======+========+=======================================================================+
| [3:0] | EPNO   | The endpoint number to update the ``enable`` and ``status`` bits for. |
+-------+--------+-----------------------------------------------------------------------+
| [4]   | ENABLE | Write a ``1`` here to enable receiving data                           |
+-------+--------+-----------------------------------------------------------------------+
| [5]   | RESET  | Write a ``1`` here to reset the ``OUT`` handler                       |
+-------+--------+-----------------------------------------------------------------------+
| [6]   | STALL  | Write a ``1`` here to stall an endpoint                               |
+-------+--------+-----------------------------------------------------------------------+

USB_OUT_STATUS
^^^^^^^^^^^^^^

`Address: 0xe0004800 + 0x44 = 0xe0004844`

    Status about the current state of the `OUT` endpoint.

    .. wavedrom::
        :caption: USB_OUT_STATUS

        {
            "reg": [
                {"name": "epno",  "bits": 4},
                {"name": "have",  "bits": 1},
                {"name": "pend",  "bits": 1},
                {"bits": 2}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+--------------------------------------------------------------+
| Field | Name | Description                                                  |
+=======+======+==============================================================+
| [3:0] | EPNO | The destination endpoint for the most recent ``OUT`` packet. |
+-------+------+--------------------------------------------------------------+
| [4]   | HAVE | ``1`` if there is data in the FIFO.                          |
+-------+------+--------------------------------------------------------------+
| [5]   | PEND | ``1`` if there is an IRQ pending.                            |
+-------+------+--------------------------------------------------------------+

USB_OUT_EV_STATUS
^^^^^^^^^^^^^^^^^

`Address: 0xe0004800 + 0x48 = 0xe0004848`

    This register contains the current raw level of the Event trigger.  Writes to this register have no effect.

    .. wavedrom::
        :caption: USB_OUT_EV_STATUS

        {
            "reg": [
                {"name": "done",  "bits": 1},
                {"bits": 7}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+---------------------------+
| Field | Name | Description               |
+=======+======+===========================+
| [0]   | DONE | Level of the `done` event |
+-------+------+---------------------------+

USB_OUT_EV_PENDING
^^^^^^^^^^^^^^^^^^

`Address: 0xe0004800 + 0x4c = 0xe000484c`

    When an Event occurs, the corresponding bit will be set in this register.  To clear the Event, set the corresponding bit in this register.

    .. wavedrom::
        :caption: USB_OUT_EV_PENDING

        {
            "reg": [
                {"name": "done",  "bits": 1},
                {"bits": 7}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+--------------------------------------------------------------------------------+
| Field | Name | Description                                                                    |
+=======+======+================================================================================+
| [0]   | DONE |                                                                                |
|       |      |             Indicates that an ``OUT`` packet has successfully been transferred |
|       |      |             from the host.  This bit must be cleared in order to receive       |
|       |      |             additional packets.                                                |
+-------+------+--------------------------------------------------------------------------------+

USB_OUT_EV_ENABLE
^^^^^^^^^^^^^^^^^

`Address: 0xe0004800 + 0x50 = 0xe0004850`

    This register enables the corresponding Events.  Write a `0` to this register to disable individual events.

    .. wavedrom::
        :caption: USB_OUT_EV_ENABLE

        {
            "reg": [
                {"name": "done",  "bits": 1},
                {"bits": 7}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+----------------------------------------+
| Field | Name | Description                            |
+=======+======+========================================+
| [0]   | DONE | Write a `1` to enable the `done` Event |
+-------+------+----------------------------------------+

