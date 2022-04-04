UART
====

Register Listing for UART
-------------------------

+------------------------------------------+-------------------------------------+
| Register                                 | Address                             |
+==========================================+=====================================+
| :ref:`UART_RXTX <UART_RXTX>`             | :ref:`0xe0001800 <UART_RXTX>`       |
+------------------------------------------+-------------------------------------+
| :ref:`UART_TXFULL <UART_TXFULL>`         | :ref:`0xe0001804 <UART_TXFULL>`     |
+------------------------------------------+-------------------------------------+
| :ref:`UART_RXEMPTY <UART_RXEMPTY>`       | :ref:`0xe0001808 <UART_RXEMPTY>`    |
+------------------------------------------+-------------------------------------+
| :ref:`UART_EV_STATUS <UART_EV_STATUS>`   | :ref:`0xe000180c <UART_EV_STATUS>`  |
+------------------------------------------+-------------------------------------+
| :ref:`UART_EV_PENDING <UART_EV_PENDING>` | :ref:`0xe0001810 <UART_EV_PENDING>` |
+------------------------------------------+-------------------------------------+
| :ref:`UART_EV_ENABLE <UART_EV_ENABLE>`   | :ref:`0xe0001814 <UART_EV_ENABLE>`  |
+------------------------------------------+-------------------------------------+

UART_RXTX
^^^^^^^^^

`Address: 0xe0001800 + 0x0 = 0xe0001800`


    .. wavedrom::
        :caption: UART_RXTX

        {
            "reg": [
                {"name": "rxtx[7:0]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


UART_TXFULL
^^^^^^^^^^^

`Address: 0xe0001800 + 0x4 = 0xe0001804`


    .. wavedrom::
        :caption: UART_TXFULL

        {
            "reg": [
                {"name": "txfull", "bits": 1},
                {"bits": 7},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


UART_RXEMPTY
^^^^^^^^^^^^

`Address: 0xe0001800 + 0x8 = 0xe0001808`


    .. wavedrom::
        :caption: UART_RXEMPTY

        {
            "reg": [
                {"name": "rxempty", "bits": 1},
                {"bits": 7},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


UART_EV_STATUS
^^^^^^^^^^^^^^

`Address: 0xe0001800 + 0xc = 0xe000180c`

    This register contains the current raw level of the Event trigger.  Writes to this register have no effect.

    .. wavedrom::
        :caption: UART_EV_STATUS

        {
            "reg": [
                {"name": "tx",  "bits": 1},
                {"name": "rx",  "bits": 1},
                {"bits": 6}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+-------------------------+
| Field | Name | Description             |
+=======+======+=========================+
| [0]   | TX   | Level of the `tx` event |
+-------+------+-------------------------+
| [1]   | RX   | Level of the `rx` event |
+-------+------+-------------------------+

UART_EV_PENDING
^^^^^^^^^^^^^^^

`Address: 0xe0001800 + 0x10 = 0xe0001810`

    When an Event occurs, the corresponding bit will be set in this register.  To clear the Event, set the corresponding bit in this register.

    .. wavedrom::
        :caption: UART_EV_PENDING

        {
            "reg": [
                {"name": "tx",  "bits": 1},
                {"name": "rx",  "bits": 1},
                {"bits": 6}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+------------------------------------------------------------------------------+
| Field | Name | Description                                                                  |
+=======+======+==============================================================================+
| [0]   | TX   | `1` if a `tx` event occurred. This Event is triggered on a **falling** edge. |
+-------+------+------------------------------------------------------------------------------+
| [1]   | RX   | `1` if a `rx` event occurred. This Event is triggered on a **falling** edge. |
+-------+------+------------------------------------------------------------------------------+

UART_EV_ENABLE
^^^^^^^^^^^^^^

`Address: 0xe0001800 + 0x14 = 0xe0001814`

    This register enables the corresponding Events.  Write a `0` to this register to disable individual events.

    .. wavedrom::
        :caption: UART_EV_ENABLE

        {
            "reg": [
                {"name": "tx",  "bits": 1},
                {"name": "rx",  "bits": 1},
                {"bits": 6}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+--------------------------------------+
| Field | Name | Description                          |
+=======+======+======================================+
| [0]   | TX   | Write a `1` to enable the `tx` Event |
+-------+------+--------------------------------------+
| [1]   | RX   | Write a `1` to enable the `rx` Event |
+-------+------+--------------------------------------+

