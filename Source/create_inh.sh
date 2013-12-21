#!/usr/bin/env bash
[[ -z "$1" ]] && echo "Missing class name" && exit 1

class="$1"

cat inh_tmpl.h.in | sed -e "s,%[^%]\+%,${class},g" > "$class"_inh.h
