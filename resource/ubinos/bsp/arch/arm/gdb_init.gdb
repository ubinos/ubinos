#
# Copyright (c) 2022 Sung Ho Park
# 
# SPDX-License-Identifier: Apache-2.0
#

set pagination off

set remote memory-write-packet-size 1024
set remote memory-read-packet-size 1024

define ushowmemx
    set $addr = $arg0
    set $len = $arg1
    set $end = $addr + $len
    set $cur = $addr
    while ($cur < $end)
        x/1wx $cur
        set $cur = $cur + 4
    end
end

define ushowmemxr
    set $addr = $arg0
    set $len = $arg1
    set $end = $addr + $len
    set $cur = $end
    while ($cur > $addr)
        set $cur = $cur - 4
        x/1wx $cur
    end
end

define ushowmems
    set $addr = $arg0
    x/1s $addr
end

define ushowstack
    ushowmemx $sp $arg0
end

define ushowstackr
    ushowmemxr $sp $arg0
end

define ushowcore
    x/5i $pc - 6
    info reg
    ushowstack $arg0
end

define ushowcorer
    x/5i $pc - 6
    info reg
    ushowstackr $arg0
end

define ushowcoreall
    x/5i $pc - 6
    info all-reg
    ushowstack $arg0
end

define ushowcoreallr
    x/5i $pc - 6
    info all-reg
    ushowstackr $arg0
end
