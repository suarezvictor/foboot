VERSION
=======

SoC Version Information
-----------------------

This block contains various information about the state of the source code
repository when this SoC was built.


Register Listing for VERSION
----------------------------

+----------------------------------------------+---------------------------------------+
| Register                                     | Address                               |
+==============================================+=======================================+
| :ref:`VERSION_MAJOR <VERSION_MAJOR>`         | :ref:`0xe0007000 <VERSION_MAJOR>`     |
+----------------------------------------------+---------------------------------------+
| :ref:`VERSION_MINOR <VERSION_MINOR>`         | :ref:`0xe0007004 <VERSION_MINOR>`     |
+----------------------------------------------+---------------------------------------+
| :ref:`VERSION_REVISION <VERSION_REVISION>`   | :ref:`0xe0007008 <VERSION_REVISION>`  |
+----------------------------------------------+---------------------------------------+
| :ref:`VERSION_GITREV3 <VERSION_GITREV3>`     | :ref:`0xe000700c <VERSION_GITREV3>`   |
+----------------------------------------------+---------------------------------------+
| :ref:`VERSION_GITREV2 <VERSION_GITREV2>`     | :ref:`0xe0007010 <VERSION_GITREV2>`   |
+----------------------------------------------+---------------------------------------+
| :ref:`VERSION_GITREV1 <VERSION_GITREV1>`     | :ref:`0xe0007014 <VERSION_GITREV1>`   |
+----------------------------------------------+---------------------------------------+
| :ref:`VERSION_GITREV0 <VERSION_GITREV0>`     | :ref:`0xe0007018 <VERSION_GITREV0>`   |
+----------------------------------------------+---------------------------------------+
| :ref:`VERSION_GITEXTRA1 <VERSION_GITEXTRA1>` | :ref:`0xe000701c <VERSION_GITEXTRA1>` |
+----------------------------------------------+---------------------------------------+
| :ref:`VERSION_GITEXTRA0 <VERSION_GITEXTRA0>` | :ref:`0xe0007020 <VERSION_GITEXTRA0>` |
+----------------------------------------------+---------------------------------------+
| :ref:`VERSION_DIRTY <VERSION_DIRTY>`         | :ref:`0xe0007024 <VERSION_DIRTY>`     |
+----------------------------------------------+---------------------------------------+
| :ref:`VERSION_MODEL <VERSION_MODEL>`         | :ref:`0xe0007028 <VERSION_MODEL>`     |
+----------------------------------------------+---------------------------------------+
| :ref:`VERSION_SEED3 <VERSION_SEED3>`         | :ref:`0xe000702c <VERSION_SEED3>`     |
+----------------------------------------------+---------------------------------------+
| :ref:`VERSION_SEED2 <VERSION_SEED2>`         | :ref:`0xe0007030 <VERSION_SEED2>`     |
+----------------------------------------------+---------------------------------------+
| :ref:`VERSION_SEED1 <VERSION_SEED1>`         | :ref:`0xe0007034 <VERSION_SEED1>`     |
+----------------------------------------------+---------------------------------------+
| :ref:`VERSION_SEED0 <VERSION_SEED0>`         | :ref:`0xe0007038 <VERSION_SEED0>`     |
+----------------------------------------------+---------------------------------------+

VERSION_MAJOR
^^^^^^^^^^^^^

`Address: 0xe0007000 + 0x0 = 0xe0007000`

    Major git tag version.  For example, this firmware was built from git tag
    ``v2.0.4``, so this value is ``2``.

    .. wavedrom::
        :caption: VERSION_MAJOR

        {
            "reg": [
                {"name": "major[7:0]", "attr": 'reset: 2', "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


VERSION_MINOR
^^^^^^^^^^^^^

`Address: 0xe0007000 + 0x4 = 0xe0007004`

    Minor git tag version.  For example, this firmware was built from git tag
    ``v2.0.4``, so this value is ``0``.

    .. wavedrom::
        :caption: VERSION_MINOR

        {
            "reg": [
                {"name": "minor[7:0]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


VERSION_REVISION
^^^^^^^^^^^^^^^^

`Address: 0xe0007000 + 0x8 = 0xe0007008`

    Revision git tag version.  For example, this firmware was built from git tag
    ``v2.0.4``, so this value is ``4``.

    .. wavedrom::
        :caption: VERSION_REVISION

        {
            "reg": [
                {"name": "revision[7:0]", "attr": 'reset: 4', "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


VERSION_GITREV3
^^^^^^^^^^^^^^^

`Address: 0xe0007000 + 0xc = 0xe000700c`

    Bits 24-31 of `VERSION_GITREV`. First 32-bits of the git revision.  This
    documentation was built from git rev ``00000000``, so this value is 0, which
    should be enough to check out the exact git version used to build this firmware.

    .. wavedrom::
        :caption: VERSION_GITREV3

        {
            "reg": [
                {"name": "gitrev[31:24]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


VERSION_GITREV2
^^^^^^^^^^^^^^^

`Address: 0xe0007000 + 0x10 = 0xe0007010`

    Bits 16-23 of `VERSION_GITREV`.

    .. wavedrom::
        :caption: VERSION_GITREV2

        {
            "reg": [
                {"name": "gitrev[23:16]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


VERSION_GITREV1
^^^^^^^^^^^^^^^

`Address: 0xe0007000 + 0x14 = 0xe0007014`

    Bits 8-15 of `VERSION_GITREV`.

    .. wavedrom::
        :caption: VERSION_GITREV1

        {
            "reg": [
                {"name": "gitrev[15:8]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


VERSION_GITREV0
^^^^^^^^^^^^^^^

`Address: 0xe0007000 + 0x18 = 0xe0007018`

    Bits 0-7 of `VERSION_GITREV`.

    .. wavedrom::
        :caption: VERSION_GITREV0

        {
            "reg": [
                {"name": "gitrev[7:0]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


VERSION_GITEXTRA1
^^^^^^^^^^^^^^^^^

`Address: 0xe0007000 + 0x1c = 0xe000701c`

    Bits 8-9 of `VERSION_GITEXTRA`. The number of additional commits beyond the git
    tag.  For example, if this value is ``1``, then the repository this was built
    from has one additional commit beyond the tag indicated in `MAJOR`, `MINOR`, and
    `REVISION`.

    .. wavedrom::
        :caption: VERSION_GITEXTRA1

        {
            "reg": [
                {"name": "gitextra[15:8]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


VERSION_GITEXTRA0
^^^^^^^^^^^^^^^^^

`Address: 0xe0007000 + 0x20 = 0xe0007020`

    Bits 0-7 of `VERSION_GITEXTRA`.

    .. wavedrom::
        :caption: VERSION_GITEXTRA0

        {
            "reg": [
                {"name": "gitextra[7:0]", "attr": 'reset: 2', "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


VERSION_DIRTY
^^^^^^^^^^^^^

`Address: 0xe0007000 + 0x24 = 0xe0007024`


    .. wavedrom::
        :caption: VERSION_DIRTY

        {
            "reg": [
                {"name": "dirty",  "attr": '1', "bits": 1},
                {"bits": 7}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+-------+------------------------------------------------------------------------+
| Field | Name  | Description                                                            |
+=======+=======+========================================================================+
| [0]   | DIRTY | Set to ``1`` if this device was built from a git repo with uncommitted |
|       |       | modifications.                                                         |
+-------+-------+------------------------------------------------------------------------+

VERSION_MODEL
^^^^^^^^^^^^^

`Address: 0xe0007000 + 0x28 = 0xe0007028`


    .. wavedrom::
        :caption: VERSION_MODEL

        {
            "reg": [
                {"name": "model",  "attr": '69', "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+-------+----------------------------------------------------------------+
| Field | Name  | Description                                                    |
+=======+=======+================================================================+
| [7:0] | MODEL | Contains information on which model device this was built for. |
|       |       |                                                                |
|       |       | +-------+-----------------------+                              |
|       |       | | Value | Description           |                              |
|       |       | +=======+=======================+                              |
|       |       | | 0x45  | Fomu EVT              |                              |
|       |       | +-------+-----------------------+                              |
|       |       | | 0x44  | Fomu DVT              |                              |
|       |       | +-------+-----------------------+                              |
|       |       | | 0x50  | Fomu PVT (production) |                              |
|       |       | +-------+-----------------------+                              |
|       |       | | 0x48  | Fomu Hacker           |                              |
|       |       | +-------+-----------------------+                              |
|       |       | | 0x3f  | Unknown model         |                              |
|       |       | +-------+-----------------------+                              |
+-------+-------+----------------------------------------------------------------+

VERSION_SEED3
^^^^^^^^^^^^^

`Address: 0xe0007000 + 0x2c = 0xe000702c`

    Bits 24-31 of `VERSION_SEED`. 32-bit seed used for the place-and-route.

    .. wavedrom::
        :caption: VERSION_SEED3

        {
            "reg": [
                {"name": "seed[31:24]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


VERSION_SEED2
^^^^^^^^^^^^^

`Address: 0xe0007000 + 0x30 = 0xe0007030`

    Bits 16-23 of `VERSION_SEED`.

    .. wavedrom::
        :caption: VERSION_SEED2

        {
            "reg": [
                {"name": "seed[23:16]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


VERSION_SEED1
^^^^^^^^^^^^^

`Address: 0xe0007000 + 0x34 = 0xe0007034`

    Bits 8-15 of `VERSION_SEED`.

    .. wavedrom::
        :caption: VERSION_SEED1

        {
            "reg": [
                {"name": "seed[15:8]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


VERSION_SEED0
^^^^^^^^^^^^^

`Address: 0xe0007000 + 0x38 = 0xe0007038`

    Bits 0-7 of `VERSION_SEED`.

    .. wavedrom::
        :caption: VERSION_SEED0

        {
            "reg": [
                {"name": "seed[7:0]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


