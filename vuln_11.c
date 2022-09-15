/*
 * Processing packet in NTPD
 */

static struct ctl_var *
ctl_getitem(
    struct ctl_var *var_list,
    char **data
)
{
    register struct ctl_var *v;
    register char *cp;
    register char *tp;
    static struct ctl_var eol = { 0, EOV, };
    static char buf[128];

    /*
     * Delete leading commas and white space
     */
    while (reqpt < reqend && (*reqpt == ',' || isspace((int)*reqpt))) {
        reqpt++;
    }

    if (reqpt >= reqend)
        return 0;

    if (var_list == (struct c tl_var *)0)
        return &eol;

    /*
     * Look for a first character match on the tag. If we find one, see if it is a full match.
     */
    v = var_list;
    cp = reqpt;
    while (!(v->flags & EOV)) {
        if (!(v->flags & PADDING) && *cp == *(v->text)) {
            tp = v->text;
            while (*tp != '\0' && *tp != '=' && cp < reqend && *cp == *tp) {
                cp++;
                tp++;
            }

            if ((*tp == '\0') || (*tp == '=')) {
                while (cp < reqend && isspace((int)*cp))
                    cp++;

                if (cp == reqend || *cp == ',') {
                    buf[0] = '\0';
                    *data = buf;
                    if (cp < reqend)
                        cp++;
                    reqpt = cp;
                    return v;
                }

                if (*cp == '=') {
                    cp++;
                    tp = buf;
                    while (cp < reqend && isspace((int)*cp))
                        cp++;

                    while (cp < reqend && *cp != ',')
                        *tp++ = *cp++;
                    if (cp < reqend)
                        cp++;
                    *tp = '\0';
                    while (isspace((int)(*(tp - 1))))
                        *(--tp) = '\0';

                    reqpt = cp;
                    *data = buf;
                    return v;
                }
            }
            cp = reqpt;
        }
        v++;
    }
    return v;
}