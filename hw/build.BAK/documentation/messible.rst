MESSIBLE
========



Messible: An Ansible for Messages

An Ansible is a system for instant communication across vast distances, from
a small portable device to a huge terminal far away.  A Messible is a message-
passing system from embedded devices to a host system.  You can use it to get
very simple printf()-style support over a debug channel.

The Messible assumes the host has a way to peek into the device's memory space.
This is the case with the Wishbone bridge, which allows both the device and
the host to access the same memory.

At its core, a Messible is a FIFO.  As long as the ``STATUS.FULL`` bit is ``0``, the
device can write data into the Messible by writing into the ``IN``.  However, if this
value is ``1``, you need to decide if you want to wait for it to empty (if the other
side is just slow), or if you want to drop the message.

From the host side, you need to read ``STATUS.HAVE`` to see if there is data
in the FIFO.  If there is, read ``OUT`` to get the most recent byte, which automatically
advances the ``READ`` pointer.


Register Listing for MESSIBLE
-----------------------------

+------------------------------------------+-------------------------------------+
| Register                                 | Address                             |
+==========================================+=====================================+
| :ref:`MESSIBLE_IN <MESSIBLE_IN>`         | :ref:`0xe0008000 <MESSIBLE_IN>`     |
+------------------------------------------+-------------------------------------+
| :ref:`MESSIBLE_OUT <MESSIBLE_OUT>`       | :ref:`0xe0008004 <MESSIBLE_OUT>`    |
+------------------------------------------+-------------------------------------+
| :ref:`MESSIBLE_STATUS <MESSIBLE_STATUS>` | :ref:`0xe0008008 <MESSIBLE_STATUS>` |
+------------------------------------------+-------------------------------------+

MESSIBLE_IN
^^^^^^^^^^^

`Address: 0xe0008000 + 0x0 = 0xe0008000`

    Write half of the FIFO to send data out the Messible. Writing to this register
    advances the write pointer automatically.

    .. wavedrom::
        :caption: MESSIBLE_IN

        {
            "reg": [
                {"name": "in[7:0]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


MESSIBLE_OUT
^^^^^^^^^^^^

`Address: 0xe0008000 + 0x4 = 0xe0008004`

    Read half of the FIFO to receive data on the Messible. Reading from this
    register advances the read pointer automatically.

    .. wavedrom::
        :caption: MESSIBLE_OUT

        {
            "reg": [
                {"name": "out[7:0]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


MESSIBLE_STATUS
^^^^^^^^^^^^^^^

`Address: 0xe0008000 + 0x8 = 0xe0008008`


    .. wavedrom::
        :caption: MESSIBLE_STATUS

        {
            "reg": [
                {"name": "full",  "bits": 1},
                {"name": "have",  "bits": 1},
                {"bits": 6}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+----------------------------------------------+
| Field | Name | Description                                  |
+=======+======+==============================================+
| [0]   | FULL | ``0`` if more data can fit into the IN FIFO. |
+-------+------+----------------------------------------------+
| [1]   | HAVE | ``1`` if data can be read from the OUT FIFO. |
+-------+------+----------------------------------------------+

