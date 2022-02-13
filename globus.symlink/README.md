[Grid certificate](https://alice-doc.github.io/alice-analysis-tutorial/start/cert.html)
================

## Obtain a digital certificate
* [Generate a new CERN Grid User certificate](https://ca.cern.ch/ca/user/Request.aspx?template=EE2User)

Proceed until you get a message saying that your certificate is ready to be downloaded: click on it
and a file called `myCertificate.p12` will be downloaded.

## Register your certificate to the ALICE Grid

This operation needs to be performed only once. With Firefox, click on [this
link](https://voms2.cern.ch:8443/voms/alice) and follow the guided procedure, after having selected
your personal certificate for authenticating.

When the registration to the VO is successful, you will receive an email informing you. The
registration procedure does not involve any modification or re-download of your current certificate.
In case you are not receiving this email, you might want to ping Latchezar Betev:
<Latchezar.Betev@cern.ch>


## Convert your certificate for using the Grid tools

Keep at hand the `myCertificate.p12` file you have previously downloaded. You need to convert it
into two files (a "certificate" and a "key") in order to use the ALICE Grid services from the
command line.

You will export your certificates to the following directory:

```
~/.globus
```

Now export the **certificate** with the following command (you will be prompted for the export
password you have selected when you have generated it):

```bash
openssl pkcs12 -clcerts -nokeys -in ~/Downloads/myCertificate.p12 -out ~/.globus/usercert.pem
```

The result will be a file called `usercert.pem` in your `~/.globus` directory. Note that
your input file ending with `.p12` may have a different name and may be stored in a different
location.

Time to export the **private key**:

```bash
openssl pkcs12 -nocerts -in ~/Downloads/myCertificate.p12 -out ~/.globus/userkey.pem
chmod 0400 ~/.globus/userkey.pem
```

When it says:

```
Enter Import Password:
```

you should provide it with the export password you have entered when you generated it. The next
question will be:

```
Enter PEM pass phrase:
```

You should provide it with _another_ password that will be used to protect the private key. You can
use the same password as before if you want, but please **do not use your CERN password** (yes, we
are stressing this point _a lot_). This question will be asked twice for confirmation.
