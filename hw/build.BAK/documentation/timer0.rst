TIMER0
======

Timer
-----

Provides a generic Timer core.

The Timer is implemented as a countdown timer that can be used in various modes:

- Polling : Returns current countdown value to software
- One-Shot: Loads itself and stops when value reaches ``0``
- Periodic: (Re-)Loads itself when value reaches ``0``

``en`` register allows the user to enable/disable the Timer. When the Timer is enabled, it is
automatically loaded with the value of `load` register.

When the Timer reaches ``0``, it is automatically reloaded with value of `reload` register.

The user can latch the current countdown value by writing to ``update_value`` register, it will
update ``value`` register with current countdown value.

To use the Timer in One-Shot mode, the user needs to:

- Disable the timer
- Set the ``load`` register to the expected duration
- (Re-)Enable the Timer

To use the Timer in Periodic mode, the user needs to:

- Disable the Timer
- Set the ``load`` register to 0
- Set the ``reload`` register to the expected period
- Enable the Timer

For both modes, the CPU can be advertised by an IRQ that the duration/period has elapsed. (The
CPU can also do software polling with ``update_value`` and ``value`` to know the elapsed duration)


Register Listing for TIMER0
---------------------------

+--------------------------------------------------+-----------------------------------------+
| Register                                         | Address                                 |
+==================================================+=========================================+
| :ref:`TIMER0_LOAD3 <TIMER0_LOAD3>`               | :ref:`0xe0002800 <TIMER0_LOAD3>`        |
+--------------------------------------------------+-----------------------------------------+
| :ref:`TIMER0_LOAD2 <TIMER0_LOAD2>`               | :ref:`0xe0002804 <TIMER0_LOAD2>`        |
+--------------------------------------------------+-----------------------------------------+
| :ref:`TIMER0_LOAD1 <TIMER0_LOAD1>`               | :ref:`0xe0002808 <TIMER0_LOAD1>`        |
+--------------------------------------------------+-----------------------------------------+
| :ref:`TIMER0_LOAD0 <TIMER0_LOAD0>`               | :ref:`0xe000280c <TIMER0_LOAD0>`        |
+--------------------------------------------------+-----------------------------------------+
| :ref:`TIMER0_RELOAD3 <TIMER0_RELOAD3>`           | :ref:`0xe0002810 <TIMER0_RELOAD3>`      |
+--------------------------------------------------+-----------------------------------------+
| :ref:`TIMER0_RELOAD2 <TIMER0_RELOAD2>`           | :ref:`0xe0002814 <TIMER0_RELOAD2>`      |
+--------------------------------------------------+-----------------------------------------+
| :ref:`TIMER0_RELOAD1 <TIMER0_RELOAD1>`           | :ref:`0xe0002818 <TIMER0_RELOAD1>`      |
+--------------------------------------------------+-----------------------------------------+
| :ref:`TIMER0_RELOAD0 <TIMER0_RELOAD0>`           | :ref:`0xe000281c <TIMER0_RELOAD0>`      |
+--------------------------------------------------+-----------------------------------------+
| :ref:`TIMER0_EN <TIMER0_EN>`                     | :ref:`0xe0002820 <TIMER0_EN>`           |
+--------------------------------------------------+-----------------------------------------+
| :ref:`TIMER0_UPDATE_VALUE <TIMER0_UPDATE_VALUE>` | :ref:`0xe0002824 <TIMER0_UPDATE_VALUE>` |
+--------------------------------------------------+-----------------------------------------+
| :ref:`TIMER0_VALUE3 <TIMER0_VALUE3>`             | :ref:`0xe0002828 <TIMER0_VALUE3>`       |
+--------------------------------------------------+-----------------------------------------+
| :ref:`TIMER0_VALUE2 <TIMER0_VALUE2>`             | :ref:`0xe000282c <TIMER0_VALUE2>`       |
+--------------------------------------------------+-----------------------------------------+
| :ref:`TIMER0_VALUE1 <TIMER0_VALUE1>`             | :ref:`0xe0002830 <TIMER0_VALUE1>`       |
+--------------------------------------------------+-----------------------------------------+
| :ref:`TIMER0_VALUE0 <TIMER0_VALUE0>`             | :ref:`0xe0002834 <TIMER0_VALUE0>`       |
+--------------------------------------------------+-----------------------------------------+
| :ref:`TIMER0_EV_STATUS <TIMER0_EV_STATUS>`       | :ref:`0xe0002838 <TIMER0_EV_STATUS>`    |
+--------------------------------------------------+-----------------------------------------+
| :ref:`TIMER0_EV_PENDING <TIMER0_EV_PENDING>`     | :ref:`0xe000283c <TIMER0_EV_PENDING>`   |
+--------------------------------------------------+-----------------------------------------+
| :ref:`TIMER0_EV_ENABLE <TIMER0_EV_ENABLE>`       | :ref:`0xe0002840 <TIMER0_EV_ENABLE>`    |
+--------------------------------------------------+-----------------------------------------+

TIMER0_LOAD3
^^^^^^^^^^^^

`Address: 0xe0002800 + 0x0 = 0xe0002800`

    Bits 24-31 of `TIMER0_LOAD`. Load value when Timer is (re-)enabled. In One-Shot
    mode, the value written to this register specifies the Timer's duration in clock
    cycles.

    .. wavedrom::
        :caption: TIMER0_LOAD3

        {
            "reg": [
                {"name": "load[31:24]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


TIMER0_LOAD2
^^^^^^^^^^^^

`Address: 0xe0002800 + 0x4 = 0xe0002804`

    Bits 16-23 of `TIMER0_LOAD`.

    .. wavedrom::
        :caption: TIMER0_LOAD2

        {
            "reg": [
                {"name": "load[23:16]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


TIMER0_LOAD1
^^^^^^^^^^^^

`Address: 0xe0002800 + 0x8 = 0xe0002808`

    Bits 8-15 of `TIMER0_LOAD`.

    .. wavedrom::
        :caption: TIMER0_LOAD1

        {
            "reg": [
                {"name": "load[15:8]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


TIMER0_LOAD0
^^^^^^^^^^^^

`Address: 0xe0002800 + 0xc = 0xe000280c`

    Bits 0-7 of `TIMER0_LOAD`.

    .. wavedrom::
        :caption: TIMER0_LOAD0

        {
            "reg": [
                {"name": "load[7:0]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


TIMER0_RELOAD3
^^^^^^^^^^^^^^

`Address: 0xe0002800 + 0x10 = 0xe0002810`

    Bits 24-31 of `TIMER0_RELOAD`. Reload value when Timer reaches ``0``. In
    Periodic mode, the value written to this register specify the Timer's period in
    clock cycles.

    .. wavedrom::
        :caption: TIMER0_RELOAD3

        {
            "reg": [
                {"name": "reload[31:24]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


TIMER0_RELOAD2
^^^^^^^^^^^^^^

`Address: 0xe0002800 + 0x14 = 0xe0002814`

    Bits 16-23 of `TIMER0_RELOAD`.

    .. wavedrom::
        :caption: TIMER0_RELOAD2

        {
            "reg": [
                {"name": "reload[23:16]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


TIMER0_RELOAD1
^^^^^^^^^^^^^^

`Address: 0xe0002800 + 0x18 = 0xe0002818`

    Bits 8-15 of `TIMER0_RELOAD`.

    .. wavedrom::
        :caption: TIMER0_RELOAD1

        {
            "reg": [
                {"name": "reload[15:8]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


TIMER0_RELOAD0
^^^^^^^^^^^^^^

`Address: 0xe0002800 + 0x1c = 0xe000281c`

    Bits 0-7 of `TIMER0_RELOAD`.

    .. wavedrom::
        :caption: TIMER0_RELOAD0

        {
            "reg": [
                {"name": "reload[7:0]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


TIMER0_EN
^^^^^^^^^

`Address: 0xe0002800 + 0x20 = 0xe0002820`

    Enable flag of the Timer. Set this flag to ``1`` to enable/start the Timer.  Set
    to ``0`` to disable the Timer.

    .. wavedrom::
        :caption: TIMER0_EN

        {
            "reg": [
                {"name": "en", "bits": 1},
                {"bits": 7},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


TIMER0_UPDATE_VALUE
^^^^^^^^^^^^^^^^^^^

`Address: 0xe0002800 + 0x24 = 0xe0002824`

    Update trigger for the current countdown value. A write to this register latches
    the current countdown value to ``value`` register.

    .. wavedrom::
        :caption: TIMER0_UPDATE_VALUE

        {
            "reg": [
                {"name": "update_value", "bits": 1},
                {"bits": 7},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


TIMER0_VALUE3
^^^^^^^^^^^^^

`Address: 0xe0002800 + 0x28 = 0xe0002828`

    Bits 24-31 of `TIMER0_VALUE`. Latched countdown value. This value is updated by
    writing to ``update_value``.

    .. wavedrom::
        :caption: TIMER0_VALUE3

        {
            "reg": [
                {"name": "value[31:24]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


TIMER0_VALUE2
^^^^^^^^^^^^^

`Address: 0xe0002800 + 0x2c = 0xe000282c`

    Bits 16-23 of `TIMER0_VALUE`.

    .. wavedrom::
        :caption: TIMER0_VALUE2

        {
            "reg": [
                {"name": "value[23:16]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


TIMER0_VALUE1
^^^^^^^^^^^^^

`Address: 0xe0002800 + 0x30 = 0xe0002830`

    Bits 8-15 of `TIMER0_VALUE`.

    .. wavedrom::
        :caption: TIMER0_VALUE1

        {
            "reg": [
                {"name": "value[15:8]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


TIMER0_VALUE0
^^^^^^^^^^^^^

`Address: 0xe0002800 + 0x34 = 0xe0002834`

    Bits 0-7 of `TIMER0_VALUE`.

    .. wavedrom::
        :caption: TIMER0_VALUE0

        {
            "reg": [
                {"name": "value[7:0]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


TIMER0_EV_STATUS
^^^^^^^^^^^^^^^^

`Address: 0xe0002800 + 0x38 = 0xe0002838`

    This register contains the current raw level of the Event trigger.  Writes to this register have no effect.

    .. wavedrom::
        :caption: TIMER0_EV_STATUS

        {
            "reg": [
                {"name": "zero",  "bits": 1},
                {"bits": 7}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+---------------------------+
| Field | Name | Description               |
+=======+======+===========================+
| [0]   | ZERO | Level of the `zero` event |
+-------+------+---------------------------+

TIMER0_EV_PENDING
^^^^^^^^^^^^^^^^^

`Address: 0xe0002800 + 0x3c = 0xe000283c`

    When an Event occurs, the corresponding bit will be set in this register.  To clear the Event, set the corresponding bit in this register.

    .. wavedrom::
        :caption: TIMER0_EV_PENDING

        {
            "reg": [
                {"name": "zero",  "bits": 1},
                {"bits": 7}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+--------------------------------------------------------------------------------+
| Field | Name | Description                                                                    |
+=======+======+================================================================================+
| [0]   | ZERO | `1` if a `zero` event occurred. This Event is triggered on a **falling** edge. |
+-------+------+--------------------------------------------------------------------------------+

TIMER0_EV_ENABLE
^^^^^^^^^^^^^^^^

`Address: 0xe0002800 + 0x40 = 0xe0002840`

    This register enables the corresponding Events.  Write a `0` to this register to disable individual events.

    .. wavedrom::
        :caption: TIMER0_EV_ENABLE

        {
            "reg": [
                {"name": "zero",  "bits": 1},
                {"bits": 7}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+----------------------------------------+
| Field | Name | Description                            |
+=======+======+========================================+
| [0]   | ZERO | Write a `1` to enable the `zero` Event |
+-------+------+----------------------------------------+

